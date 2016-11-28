#ifndef __RBM_H__
#define __RBM_H__

#include <matrix/Matrix.h>

namespace libcrbm
{
  class RBM
  {
    public:

      RBM(int n, int m, int k);
      // ~RBM();

      //RBM(const RBM);
      //RBM operator=(const RBM);

      void initRandomWeights(double w = 0.01);
      void initHiddenBiasValues(double b = 0.01);
      void initOutputBiasValues(double c = 0.01);

      int n() {return _n;};
      int m() {return _m;};
      int k() {return _k;};

      double W(int i, int j) {return _W(i,j);};
      double V(int i, int j) {return _V(i,j);};
      double b(int i)        {return _b(i,0);};
      double c(int i)        {return _c(i,0);};

      void setW(Matrix W) {_W = W;};
      void setV(Matrix V) {_V = V;};
      void setb(Matrix b) {_b = b;};
      void setc(Matrix c) {_c = c;};

    protected:

      double sigm(double v);

      int    _n;            // number of output units
      int    _m;            // number of hidden units
      int    _k;            // number of input units
      int    _uditerations; // number of up-down iterations
      double _alpha;        // learning rate
      double _momentum;     // contribution of the previous gradient
      double _weightcost;   // weight cost for L2
      double _pertubation;  // add randomness to the data
      int    _numepochs;    // number of training epochs
      int    _batchsize;    // size of training data batches

      Matrix _W;            // interaction weights between hidden and outputs
      Matrix _V;            // interaction weights between hidden and inputs
      Matrix _b;            // bias values for output
      Matrix _c;            // bias values for hidden

      Matrix _vW;           // for the momentum
      Matrix _vV;           // for the momentum
      Matrix _vb;           // for the momentum
      Matrix _vc;           // for the momentum
  };
}

#endif // __RBM_H__
