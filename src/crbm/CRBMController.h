#ifndef __CRBM_CONTROLLER_H__
#define __CRBM_CONTROLLER_H__

#include <stdint.h>
#include <vector>

using namespace std;

class CRBMController
{
  public:
    CRBMController(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits);
    ~CRBMController();

    void update(double* sensors, double* actuators);

    //CRBMController(const CRBMController);
    //CRBMController operator=(const CRBMController);

  private:

    int _bins;
    int _nrOfSensors;
    int _nrOfActuators;

    int _nrOfInputUnits;
    int _nrOfHiddenUnits;
    int _nrOfOutputUnits;

    vector<uint64_t> _inputsI;
    vector<uint64_t> _outputsI;

    vector<double>   _inputsD;
    vector<double>   _outputsD;

};


#endif // __CRBM_CONTROLLER_H__
