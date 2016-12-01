#ifndef __RBM_H__
#define __RBM_H__

#include <matrix/Matrix.h>

namespace libcrbm
{
  class RBM
  {
    public:

      RBM(int n, int m, int k, int uditerations);
      // ~RBM();

      //RBM(const RBM);
      //RBM operator=(const RBM);

      void initRandomWeights(double w = 0.01);
      void initInputBiasValues(double b = 0.01);
      void initHiddenBiasValues(double c = 0.01);

      int n() {return _n;};
      int m() {return _m;};
      int k() {return _k;};

      double W(int i, int j) {return _W(i,j);};
      double V(int i, int j) {return _V(i,j);};
      double b(int i)        {return _b(i,0);};
      double c(int i)        {return _c(i,0);};

      void setW(Matrix& W);
      void setV(Matrix& V);
      void setb(Matrix& b);
      void setc(Matrix& c);

    protected:

      double sigm(double v);

      int    _n;            // number of output units
      int    _m;            // number of hidden units
      int    _k;            // number of input units
      int    _uditerations; // number of up-down iterations

      Matrix _W;            // interaction weights between hidden and outputs
      Matrix _Wt;           // transposed W
      Matrix _V;            // interaction weights between hidden and inputs
      Matrix _b;            // bias values for output
      Matrix _c;            // bias values for hidden
  };
}

#endif // __RBM_H__
