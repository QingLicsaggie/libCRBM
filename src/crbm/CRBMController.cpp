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
                   u,
                   _bins);

  _tmpInput        = new double[_unitsPerSenAct];
  _tmpOutput       = new double[_unitsPerSenAct];
}

CRBMController::CRBMController(string filename)
{
  _crbm           = CRBMIO::read(filename);
  _bins           = _crbm->bins();
  _unitsPerSenAct = (int)ceil(log2(_bins));
  _nrOfSensors    = _crbm->n() / _unitsPerSenAct;
  _nrOfActuators  = _crbm->k() / _unitsPerSenAct;
  cout << "Bins: " << _bins << endl;
  cout << "Nr. of Sensors: " << _nrOfSensors << endl;
  cout << "Nr. of Actuators: " << _nrOfActuators << endl;

  _d              = new Discretiser(_bins, -1.0, 1.0);

  _tmpInput       = new double[_unitsPerSenAct];
  _tmpOutput      = new double[_unitsPerSenAct];

  _y.resize(_nrOfSensors   * _unitsPerSenAct, 1);
  _x.resize(_nrOfActuators * _unitsPerSenAct, 1);

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

  // cout << _y << endl;

  _crbm->control(_y, _x);

  index = 0;
  for(int i = 0; i < _nrOfActuators; i++)
  {
    for(int j = 0; j < _unitsPerSenAct; j++)
    {
      _tmpOutput[j] = _x(index++,0);
    }
    actuators[i] = _d->doublearray2double(_tmpOutput);
  }
}
