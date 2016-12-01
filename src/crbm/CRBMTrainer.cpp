#include <crbm/CRBMTrainer.h>
#include <crbm/Discretiser.h>
#include <crbm/Discretiser.h>
#include <crbm/Random.h>

#include <entropy++/Csv.h>
#include <entropy++/Container.h>

#include <glog/logging.h>

#include <math.h>

CRBMTrainer::CRBMTrainer(int    bins,
                         int    uditerations,
                         int    numepochs,
                         int    batchsize,
                         double alpha,
                         double momentum,
                         double weightcost,
                         double pertubation)
{
  _bins          = bins;
  _uditerations  = uditerations;
  _numepochs     = numepochs;
  _batchsize     = batchsize;
  _alpha         = alpha;
  _momentum      = momentum;
  _weightcost    = weightcost;
  _pertubation   = pertubation;
  _unitPerSenAct = (int)ceil(log2(_bins));
}

CRBMTrainer::~CRBMTrainer()
{
}

void CRBMTrainer::train(string inputFilename, string outputFilename, int m)
{
  VLOG(10) << "reading S-file: " << inputFilename;
  entropy::DContainer* input  = entropy::Csv::read(inputFilename);
  VLOG(20) << "Sensors:   " << endl << *input;
  if(VLOG_IS_ON(30)) entropy::Csv::write("s.csv", input);

  VLOG(10) << "reading A-file: " << outputFilename;
  entropy::DContainer* output = entropy::Csv::read(outputFilename);
  VLOG(20) << "Actuators: " << endl << *output;
  if(VLOG_IS_ON(30)) entropy::Csv::write("a.csv", output);

  input->setBinSizes(_bins);
  input->setDomains(-1.0, 1.0);

  output->setBinSizes(_bins);
  output->setDomains(-1.0, 1.0);

  entropy::ULContainer* ic = input->discretiseByColumn();
  VLOG(20) << "Binned Sensors:   " << endl << *ic;
  if(VLOG_IS_ON(30)) entropy::Csv::write("ds.csv", ic);

  entropy::ULContainer* oc = output->discretiseByColumn();
  VLOG(20) << "Binned Actuators: " << endl << *oc;
  if(VLOG_IS_ON(30)) entropy::Csv::write("da.csv", oc);

  _nrOfSensors   = input->columns();
  _nrOfActuators = output->columns();

  VLOG(10) << "Nr. of Sensors:   " << _nrOfSensors;
  VLOG(10) << "Nr. of Actuators: " << _nrOfActuators;

  int n = _nrOfSensors   * _unitPerSenAct;
  int k = _nrOfActuators * _unitPerSenAct;

  entropy::IContainer* binarisedInput  = new entropy::IContainer(ic->rows(), ic->columns() * _unitPerSenAct);
  entropy::IContainer* binarisedOutput = new entropy::IContainer(oc->rows(), oc->columns() * _unitPerSenAct);

  double values[_unitPerSenAct];
  for(int r = 0; r < ic->rows(); r++)
  {
    for(int c = 0; c < ic->columns(); c++)
    {
      Discretiser::binarise(ic->get(r,c), values, _unitPerSenAct);
      for(int v = 0; v < _unitPerSenAct; v++)
      {
        *binarisedInput << values[v];
      }
    }
  }
  VLOG(20) << "Binarised Sensors:" << endl << *binarisedInput;
  if(VLOG_IS_ON(30)) entropy::Csv::write("bs.csv", binarisedInput);

  for(int r = 0; r < oc->rows(); r++)
  {
    for(int c = 0; c < oc->columns(); c++)
    {
      Discretiser::binarise(oc->get(r,c), values, _unitPerSenAct);
      for(int v = 0; v < _unitPerSenAct; v++)
      {
        *binarisedOutput << values[v];
      }
    }
  }
  VLOG(20) << "Binarised Actuators:" << endl << *binarisedOutput;
  if(VLOG_IS_ON(30)) entropy::Csv::write("ba.csv", binarisedOutput);

  delete input;
  delete output;


  VLOG(10) << "Creating CRBM with " << n << ", " << m << ", " << k;

  _crbm = new CRBM(n, m, k, _uditerations);
  _crbm->initRandomWeights(0.01);

  // initialise b based on the data
  VLOG(10) << "Constructing b with " << n << " entries";
  Matrix b(n, 1);
  for(int c = 0; c < n; c++)
  {
    double p = 0.0;
    int colsum = binarisedInput->colSum(c);
    if(colsum == binarisedInput->rows())
    {
      p = ((float)(binarisedInput->rows()-1)/(float)(binarisedInput->rows()));
    }
    else if(colsum == 0)
    {
      p = 1.0/(float)(binarisedInput->rows());
    }
    else
    {
      p = ((float)colsum)/((float)binarisedInput->rows());
    }
    b(c,0) = p;
  }
  VLOG(20) << b;
  _crbm->setb(b);

  int length = binarisedInput->rows();

  VLOG(20) << "Copying binarised data to matrix";
  Matrix S(binarisedInput->rows(),  binarisedInput->columns());
  Matrix A(binarisedOutput->rows(), binarisedOutput->columns());

  for(int r = 0; r < binarisedInput->rows(); r++)
  {
    for(int c = 0; c < binarisedInput->columns(); c++)
    {
      S(r,c) = binarisedInput->get(r,c);
    }
  }

  for(int r = 0; r < binarisedOutput->rows(); r++)
  {
    for(int c = 0; c < binarisedOutput->columns(); c++)
    {
      A(r,c) = binarisedOutput->get(r,c);
    }
  }
  VLOG(40) << "S Matrix" << endl << S;
  VLOG(40) << "A Matrix" << endl << A;

  Matrix SBatch(S.cols(), _batchsize);
  Matrix ABatch(A.cols(), _batchsize);

  _crbm->initLearning(_batchsize);

  // Let the training begin
  VLOG(10) << "Training begins, with " << _numepochs << " epochs and batch size of " << _batchsize;
  for(int i = 0; i < _numepochs; i++)
  {
    int dataStartIndex = Random::rand(0, length - _batchsize);
    __copy(SBatch, S, dataStartIndex);
    __copy(ABatch, A, dataStartIndex);

    _crbm->up(SBatch, ABatch);
  }
}

void CRBMTrainer::__copy(Matrix& dst, const Matrix& src, int index)
{
  for(int r = 0; r < dst.rows(); r++)
  {
    for(int c = 0; c < dst.cols(); c++)
    {
      dst(r,c) = src(index + c, r);
    }
  }
}

