#include <crbm/CRBMTrainer.h>
#include <crbm/Discretiser.h>
#include <crbm/Discretiser.h>
#include <crbm/Random.h>
#include <crbm/ext/progressbar.h>
#include <crbm/CRBMIO.h>

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
  _usePB         = true;
}

CRBMTrainer::~CRBMTrainer()
{
}

void CRBMTrainer::train(string inputFilename, string outputFilename, string out, int m)
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

  _crbm = new CRBM(n, m, k, _uditerations, _bins);
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

  VLOG(10) << "Batch size: " << _batchsize;
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

  progressbar *progress;
  if(_usePB) progress = progressbar_new("Training", _numepochs);

  // Let the training begin
  VLOG(10) << "Training begins, with " << _numepochs << " epochs and batch size of " << _batchsize;
  for(int i = 0; i < _numepochs; i++)
  {
    VLOG(10) << "Epoch " << i;
    int dataStartIndex = Random::rand(0, length - _batchsize);
    VLOG(10) << "Start index " << dataStartIndex;
    __copy(SBatch, S, dataStartIndex);
    VLOG(30) << SBatch;
    __copy(ABatch, A, dataStartIndex);
    VLOG(30) << ABatch;
    __randomAInit(AInit);
    VLOG(30) << AInit;

    _crbm->up(SBatch, ABatch);
    Matrix z1 = _crbm->z();
    VLOG(30) << "Z1:";
    VLOG(30) << z1;
    // cout << "z1:" << endl << z1 << endl;
    _crbm->learn(SBatch, AInit);
    Matrix z2 = _crbm->z();
    VLOG(30) << "Z2:";
    VLOG(30) << z2;
    Matrix Agenerated = _crbm->x();
    VLOG(30) << "A generated:";
    VLOG(30) << Agenerated;

    for(int c = 0; c < _batchsize; c++)
    {
      Eb = 0.0;
      for(int r = 0; r < n; r++)
      {
        Eb(r,0) += ABatch(r, c) - Agenerated(r, c);
      }
    }
    Eb /= (double)_batchsize;
    VLOG(30) << "E[b]:";
    VLOG(30) << Eb;

    for(int c = 0; c < _batchsize; c++)
    {
      Ec = 0.0;
      for(int r = 0; r < m; r++)
      {
        Ec(r,0) += z1(r, c) - z1(r, c);
      }
    }
    Ec /= (double)_batchsize;
    VLOG(30) << "E[c]:";
    VLOG(30) << Ec;

    EW = z1 * ABatch.T() - z2 * Agenerated.T();
    VLOG(30) << "E[W]:";
    VLOG(30) << EW;

    EV = z1 * SBatch.T() - z2 * SBatch.T();
    VLOG(30) << "E[V]:";
    VLOG(30) << EV;

    tmp = _alpha * Eb;
    _crbm->changeb(tmp);
    VLOG(30) << "New b:";
    VLOG(30) << _crbm->b();

    tmp = _alpha * Ec;
    _crbm->changec(tmp);
    VLOG(30) << "New c:";
    VLOG(30) << _crbm->c();

    newW = _crbm->W() + _alpha * EW;
    VLOG(30) << "New W:";
    VLOG(30) << newW;

    newV = _crbm->V() + _alpha * EV;
    VLOG(30) << "New V:";
    VLOG(30) << newV;

    if(_momentum > 0.0)
    {
      tmp = (_alpha * _momentum) * _vb;
      _crbm->changeb(tmp);
      VLOG(30) << "MOMENTUM new W:";
      VLOG(30) << newW;
      tmp = (_alpha * _momentum) * _vb;
      _crbm->changec(tmp);
      VLOG(30) << "MOMENTUM new V:";
      VLOG(30) << newV;
      // newW = newW + _alpha * _momentum * _vW;
      // newV = newV + _alpha * _momentum * _vV;

      _vb = Eb;
      VLOG(30) << "vb:";
      VLOG(30) << _vb;
      _vc = Ec;
      VLOG(30) << "vc:";
      VLOG(30) << _vc;
      _vW = EW;
      VLOG(30) << "vW:";
      VLOG(30) << _vW;
      _vV = EV;
      VLOG(30) << "vV:";
      VLOG(30) << _vV;
    }

    if(_weightcost > 0.0)
    {
      newW = (1.0 - _weightcost) * newW;
      VLOG(30) << "WEIGHT COST new W:";
      VLOG(30) << newW;
      newV = (1.0 - _weightcost) * newV;
      VLOG(30) << "WEIGHT COST new V:";
      VLOG(30) << newV;
    }

    _crbm->setW(newW);
    _crbm->setV(newV);

    if(_usePB) progressbar_inc(progress);
    if(i % 1000 == 0) CRBMIO::write(out, _crbm);
  }
  if(_usePB) progressbar_finish(progress);

  CRBMIO::write(out, _crbm);
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

void CRBMTrainer::setUseProgressBar(bool usePB)
{
  _usePB = usePB;
}
