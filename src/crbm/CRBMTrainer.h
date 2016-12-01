#ifndef __CRBM_TRAINER_H__
#define __CRBM_TRAINER_H__

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
    class CRBMTrainer : public CRBM
    {
      public:
        CRBMTrainer(int bins,
                    int nrOfSensors,
                    int nrOfActuators,
                    int nrOfHiddenUnits,
                    int uditerations);
        ~CRBMTrainer();

        void setInputTrainingData(Matrix& input);
        void setOutputTrainingData(Matrix& output);

        void train();

        //CRBMTrainer(const CRBMTrainer);
        //CRBMTrainer operator=(const CRBMTrainer);

      private:
        void         __initialiseb();

        Matrix       _input;
        Matrix       _output;

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

        double       _alpha;         // learning rate
        double       _momentum;      // contribution of the previous gradient
        double       _weightcost;    // weight cost for L2
        double       _pertubation;   // add randomness to the data
        int          _numepochs;     // number of training epochs
        int          _batchsize;     // size of training data batches
        Matrix       _vW;            // for the momentum
        Matrix       _vV;            // for the momentum
        Matrix       _vb;            // for the momentum
        Matrix       _vc;            // for the momentum

    };
  }
}

#endif // __CRBM_TRAINER_H__
