#include <crbm/CRBMController.h>

#include <crbm/Discretiser.h>

#include <math.h>

CRBMController::CRBMController(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits)
{
  _bins            = bins;
  _nrOfSensors     = nrOfSensors;
  _nrOfActuators   = nrOfActuators;
  _nrOfHiddenUnits = nrOfHiddenUnits;

  _nrOfInputUnits  = _nrOfSensors   * (int)pow(2, _bins);
  _nrOfOutputUnits = _nrOfActuators * (int)pow(2, _bins);
}

CRBMController::~CRBMController()
{
}

void CRBMController::update(double* sensors, double* actuators)
{
}
