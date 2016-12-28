#ifndef __CRBM_CONTROLLER_H__
#define __CRBM_CONTROLLER_H__

#include <matrix/Matrix.h>
#include <crbm/Discretiser.h>
#include <crbm/CRBM.h>
#include <crbm/CRBMIO.h>

#include <stdint.h>
#include <vector>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

namespace libcrbm
{
  namespace binary
  {
    class CRBMController
    {
      public:
        CRBMController(int bins,
                       int nrOfSensors,
                       int nrOfActuators,
                       int nrOfHiddenUnits,
                       int uditerations);
        CRBMController(string filename);
        ~CRBMController();

        void update(double* sensors, double* actuators);

        void setW(Matrix& W)       {_crbm->setW(W);};
        void setV(Matrix& V)       {_crbm->setV(V);};
        void setb(Matrix& b)       {_crbm->setb(b);};
        void setc(Matrix& c)       {_crbm->setc(c);};
        void setCRBM(CRBM* crbm)   {_crbm = crbm;};
        void read(string filename) {_crbm = CRBMIO::read(filename);};

        //CRBMController(const CRBMController);
        //CRBMController operator=(const CRBMController);

      private:

        int     _bins;
        int     _nrOfSensors;
        int     _nrOfActuators;

        int     _nrOfInputUnits;
        int     _nrOfHiddenUnits;
        int     _nrOfOutputUnits;

        Matrix  _y;
        Matrix  _x;

        double* _tmpInput;
        double* _tmpOutput;

        int     _unitsPerSenAct; // nr of unit for each sensor and actuator

        Discretiser* _d;
        CRBM* _crbm;
    };
  }
}

#endif // __CRBM_CONTROLLER_H__
