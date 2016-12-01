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
  Matrix AInit(A.cols(),  _batchsize);

  Matrix Eb(n,1);
  Matrix Ec(m,1);
  Matrix EW(m,n);
  Matrix EV(m,k);
  Matrix newb(1,1);
  Matrix newc(1,1);
  Matrix newV(1,1);
  Matrix newW(1,1);

  _crbm->initLearning(_batchsize);
  Matrix tmp(0,0);

  _vb.resize(n,1);
  _vc.resize(n,1);
  _vW.resize(m,n);
  _vV.resize(m,k);

  // Let the training begin
  VLOG(10) << "Training begins, with " << _numepochs << " epochs and batch size of " << _batchsize;
  for(int i = 0; i < _numepochs; i++)
  {
    cout << i << endl;
    int dataStartIndex = Random::rand(0, length - _batchsize);
    __copy(SBatch, S, dataStartIndex);
    __copy(ABatch, A, dataStartIndex);
    __randomAInit(AInit);

    _crbm->up(SBatch, ABatch);
    Matrix z1 = _crbm->z();
    // cout << "z1:" << endl << z1 << endl;
    _crbm->learn(SBatch, AInit);
    Matrix z2 = _crbm->z();
    Matrix Agenerated = _crbm->x();
    // cout << "z2:" << endl << z2 << endl;

    for(int c = 0; c < _batchsize; c++)
    {
      Eb = 0.0;
      for(int r = 0; r < n; r++)
      {
        Eb(r,0) += ABatch(r, c) - Agenerated(r, c);
      }
    }
    Eb /= (double)_batchsize;

    for(int c = 0; c < _batchsize; c++)
    {
      Ec = 0.0;
      for(int r = 0; r < m; r++)
      {
        Ec(r,0) += z1(r, c) - z1(r, c);
      }
    }
    Ec /= (double)_batchsize;

    EW = z1 * ABatch.T() - z2 * Agenerated.T();
    EV = z1 * SBatch.T() - z2 * SBatch.T();

    tmp = _alpha * Eb;
    _crbm->changeb(tmp);
    tmp = _alpha * Ec;
    _crbm->changec(tmp);

    newW = _crbm->W() + _alpha * EW;
    newV = _crbm->V() + _alpha * EV;

    if(_momentum > 0.0)
    {
      tmp = (_alpha * _momentum) * _vb;
      _crbm->changeb(tmp);
      // tmp = _alpha * _momentum * _vb;
      // _crbm->changec(tmp);
      // newW = newW + _alpha * _momentum * _vW;
      // newV = newV + _alpha * _momentum * _vV;
    }

    // if(_weightcost > 0.0)
    // {
      // newW = (1.0 - _weightcost) * newW;
      // newV = (1.0 - _weightcost) * newV;
    // }

    // _vb = Eb;
    // _vc = Ec;
    // _vW = EW;
    // _vV = EV;

    _crbm->setW(newW);
    _crbm->setV(newV);

  }
}

void CRBMTrainer::__randomAInit(Matrix& A)
{
  for(int r = 0; r < A.rows(); r++)
  {
    for(int c = 0; c < A.cols(); c++)
    {
      A(r,c) = (Random::unit() < 0.5)?0:1;
    }
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

