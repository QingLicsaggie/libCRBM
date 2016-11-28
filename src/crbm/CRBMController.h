#ifndef __CRBM_CONTROLLER_H__
#define __CRBM_CONTROLLER_H__

#include <matrix/Matrix.h>
#include <crbm/Discretiser.h>
#include <crbm/CRBM.h>

#include <stdint.h>
#include <vector>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

namespace libcrbm
{
  namespace binary
  {
    class CRBMController : public CRBM
    {
      public:
        CRBMController(int bins, int nrOfSensors, int nrOfActuators, int nrOfHiddenUnits);
        ~CRBMController();

        void update(double* sensors, double* actuators);

        //CRBMController(const CRBMController);
        //CRBMController operator=(const CRBMController);

      private:

        int          _bins;
        int          _nrOfSensors;
        int          _nrOfActuators;

        int          _nrOfInputUnits;
        int          _nrOfHiddenUnits;
        int          _nrOfOutputUnits;

        Matrix       _binaryInput;
        Matrix       _binaryOutput;

        double*      _tmpInput;
        double*      _tmpOutput;

        int          _unitPerSenAct; // nr of unit for each sensor and actuator

        Discretiser* _d;
    };
  }
}

#endif // __CRBM_CONTROLLER_H__
