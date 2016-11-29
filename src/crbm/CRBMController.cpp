#include <crbm/CRBMController.h>

#include <crbm/Discretiser.h>

#include <math.h>

CRBMController::CRBMController(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits)
  : _binaryInput(1,1),
    _binaryOutput(1,1),
    CRBM((int)ceil(log2(bins)) * nrOfSensors,
         nrOfHiddenUnits,
         (int)ceil(log2(bins)) * nrOfActuators)
{
  _bins            = bins;
  _nrOfSensors     = nrOfSensors;
  _nrOfActuators   = nrOfActuators;

  _unitPerSenAct   = (int)ceil(log2(_bins));

  _tmpInput        = new double[_unitPerSenAct];
  _tmpOutput       = new double[_unitPerSenAct];

  _d               = new Discretiser(bins, -1.0, 1.0);

  _binaryInput.resize(_nrOfSensors    * _unitPerSenAct, 1);
  _binaryOutput.resize(_nrOfActuators * _unitPerSenAct, 1);

  // : RBM(n, m, k), _x(n,1), _y(m,1), _z(1,k)
}

CRBMController::~CRBMController()
{
  delete _tmpInput;
  delete _tmpOutput;
  delete _d;
}

void CRBMController::update(double* sensors, double* actuators)
{
  int index = 0;
  for(int i = 0; i < _nrOfSensors; i++)
  {
    _d->double2doublearray(sensors[i], _tmpInput);
    for(int j = 0; j < _unitPerSenAct; j++)
    {
      _binaryInput(index++,0) = _tmpInput[j];
    }
  }

  control(_binaryInput, _binaryOutput);

  index = 0;
  for(int i = 0; i < _nrOfActuators; i++)
  {
    for(int j = 0; j < _unitPerSenAct; j++)
    {
      _tmpOutput[j] = _binaryOutput(index++,0);
    }
    actuators[i] = _d->doublearray2double(_tmpOutput);
  }
}

