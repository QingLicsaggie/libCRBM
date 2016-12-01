#ifndef __CRBM_H__
#define __CRBM_H__

#include <matrix/Matrix.h>

namespace libcrbm
{
  namespace binary
  {
    class CRBM 
    {
      public:

        CRBM(int k, int n, int m, int uditerations);
        ~CRBM();

        void learn(Matrix& x, Matrix& y);
        void control(Matrix& x, Matrix& y);

        void up(Matrix& y, Matrix& x);
        void down(Matrix& z);

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

        const Matrix& x() { return _x; }
        const Matrix& y() { return _y; }
        const Matrix& z() { return _z; }
        void  initLearning(int n);

      private:

        double __sigm(double v);

        int    _n;            // number of output units
        int    _m;            // number of hidden units
        int    _k;            // number of input units
        int    _uditerations; // number of up-down iterations

        Matrix _W;            // interaction weights between hidden and outputs
        Matrix _Wt;           // transposed W
        Matrix _V;            // interaction weights between hidden and inputs
        Matrix _b;            // bias values for output
        Matrix _c;            // bias values for hidden

        Matrix _x;            // input
        Matrix _y;            // hidden
        Matrix _z;            // output

        bool _learningInitialised;

    };
  }
}

#endif // __CRBM_H__

