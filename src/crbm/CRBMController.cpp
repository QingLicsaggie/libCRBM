#include <crbm/CRBMController.h>

#include <crbm/Discretiser.h>

#include <math.h>

CRBMController::CRBMController(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits, int u)
  : _x(1,1), _y(1,1)
{
  _bins            = bins;
  _nrOfSensors     = nrOfSensors;
  _nrOfActuators   = nrOfActuators;
  _unitsPerSenAct  = (int)ceil(log2(bins));

  _d               = new Discretiser(bins, -1.0, 1.0);

  _y.resize(_nrOfSensors   * _unitsPerSenAct, 1);
  _x.resize(_nrOfActuators * _unitsPerSenAct, 1);

  _crbm = new CRBM(_unitsPerSenAct * nrOfSensors,     // k
                   nrOfHiddenUnits,                   // m
                   _unitsPerSenAct * nrOfActuators,   // n
                   u);

  _tmpInput        = new double[_unitsPerSenAct];
  _tmpOutput       = new double[_unitsPerSenAct];
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
    for(int j = 0; j < _unitsPerSenAct; j++)
    {
      _y(index++,0) = _tmpInput[j];
    }
  }

  _crbm->control(_y, _x);

  index = 0;
  for(int i = 0; i < _nrOfActuators; i++)
  {
    actuators[i] = _d->doublearray2double(_tmpOutput);
    for(int j = 0; j < _unitsPerSenAct; j++)
    {
      _tmpOutput[j] = _x(index++,0);
    }
  }
}

