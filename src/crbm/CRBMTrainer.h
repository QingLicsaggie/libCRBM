#ifndef __CRBM_TRAINER_H__
#define __CRBM_TRAINER_H__

#include <matrix/Matrix.h>
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
    class CRBMTrainer
    {
      public:
        CRBMTrainer(int    bins,
                    int    uditerations,
                    int    numepochs,
                    int    batchsize,
                    double alpha,
                    double momentum,
                    double weightcost,
                    double pertubation);

        ~CRBMTrainer();

        void train(string inputFilename, string outputFilename, int m);

      private:
        void   __copy(Matrix& dst, const Matrix& src, int index);
        void   __randomAInit(Matrix& a);

        int    _bins;
        int    _batchsize;     // size of training data batches
        int    _numepochs;     // number of training epochs
        int    _unitPerSenAct; // nr of unit for each sensor and actuator
        int    _uditerations;  // nr of up-down iterations
        double _alpha;         // learning rate
        double _momentum;      // contribution of the previous gradient
        double _pertubation;   // add randomness to the data
        double _weightcost;    // weight cost for L2

        int    _nrOfSensors;
        int    _nrOfActuators;

        int    _nrOfInputUnits;
        int    _nrOfHiddenUnits;
        int    _nrOfOutputUnits;

        Matrix _vW;            // for the momentum
        Matrix _vV;            // for the momentum
        Matrix _vb;            // for the momentum
        Matrix _vc;            // for the momentum

        CRBM*  _crbm;

    };
  }
}

#endif // __CRBM_TRAINER_H__
