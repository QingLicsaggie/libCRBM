#ifndef __CRBM_TRAINER_H__
#define __CRBM_TRAINER_H__

#include <crbm/CRBMMatrix.h>
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
                    double perturbation,
                    string init = "");

        ~CRBMTrainer();

        void train(string inputFilename, string outputFilename, string out, int m = 0);
        void setUseProgressBar(bool usePB);

      private:
        void   __copy(CRBMMatrix& dst, const CRBMMatrix& src, int index);
        void   __randomABinary(CRBMMatrix& a);

        int    _bins;
        int    _batchsize;     // size of training data batches
        int    _numepochs;     // number of training epochs
        int    _unitPerSenAct; // nr of unit for each sensor and actuator
        int    _uditerations;  // nr of up-down iterations
        double _alpha;         // learning rate
        double _momentum;      // contribution of the previous gradient
        double _perturbation;  // add randomness to the data
        double _weightcost;    // weight cost for L2

        int    _nrOfSensors;
        int    _nrOfActuators;

        int    _nrOfInputUnits;
        int    _nrOfHiddenUnits;
        int    _nrOfOutputUnits;

        bool   _usePB;

        CRBMMatrix _vW;            // for the momentum
        CRBMMatrix _vV;            // for the momentum
        CRBMMatrix _vb;            // for the momentum
        CRBMMatrix _vc;            // for the momentum

        CRBM*  _crbm;

    };
  }
}

#endif // __CRBM_TRAINER_H__
