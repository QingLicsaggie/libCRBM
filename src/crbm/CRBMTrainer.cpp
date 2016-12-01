#include <crbm/CRBMTrainer.h>

#include <crbm/Discretiser.h>

#include <math.h>

CRBMTrainer::CRBMTrainer(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits, int u)
  : _binaryInput(1,1),
    _binaryOutput(1,1),
    CRBM((int)ceil(log2(bins)) * nrOfSensors,
         nrOfHiddenUnits,
         (int)ceil(log2(bins)) * nrOfActuators,
         u)
{
  _bins            = bins;
  _nrOfSensors     = nrOfSensors;
  _nrOfActuators   = nrOfActuators;

  _unitPerSenAct   = (int)ceil(log2(_bins));

    _alpha        = 0.0;
    _momentum     = 0.0;
    _weightcost   = 0.0;
    _pertubation  = 0.0;
    _numepochs    = 0;
    _batchsize    = 0;

  _tmpInput        = new double[_unitPerSenAct];
  _tmpOutput       = new double[_unitPerSenAct];

  _d               = new Discretiser(bins, -1.0, 1.0);

  _binaryInput.resize(_nrOfSensors    * _unitPerSenAct, 1);
  _binaryOutput.resize(_nrOfActuators * _unitPerSenAct, 1);

  // : RBM(n, m, k), _x(n,1), _y(m,1), _z(1,k)
}

CRBMTrainer::~CRBMTrainer()
{
  delete _tmpInput;
  delete _tmpOutput;
  delete _d;
}

void CRBMTrainer::setInputTrainingData(Matrix& input)
{
  _input = input;
}

void CRBMTrainer::setOutputTrainingData(Matrix& output)
{
  _output = output;
}

void CRBMTrainer::__initialiseb()
{
}

void CRBMTrainer::train()
{
}
