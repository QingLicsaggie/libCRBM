#ifndef __CRBM_H__
#define __CRBM_H__

#include <crbm/CRBMMatrix.h>

namespace libcrbm
{
  namespace binary
  {
    class CRBM
    {
      public:

        CRBM(int k, int n, int m, int uditerations, int bins);
        ~CRBM();

        void learn(CRBMMatrix& x, CRBMMatrix& y);
        void control(CRBMMatrix& x, CRBMMatrix& y);

        void up(CRBMMatrix& y, CRBMMatrix& x);
        void down(CRBMMatrix& z, CRBMMatrix& x);

        void initRandomWeights(double w = 0.01);
        void initInputBiasValues(double b = 0.01);
        void initHiddenBiasValues(double c = 0.01);

        int n() {return _n;};
        int m() {return _m;};
        int k() {return _k;};
        int uditerations() {return _uditerations;};

        double W(int i, int j) {return _W(i,j);};
        double V(int i, int j) {return _V(i,j);};
        double b(int i)        {return _b(i,0);};
        double c(int i)        {return _c(i,0);};

        const CRBMMatrix& W() {return _W;};
        const CRBMMatrix& V() {return _V;};
        const CRBMMatrix& b() {return _b;};
        const CRBMMatrix& c() {return _c;};

        void changeb(CRBMMatrix& db);
        void changec(CRBMMatrix& dc);
        void changeb(double alpha);
        void changec(double alpha);

        void setW(CRBMMatrix& W);
        void setV(CRBMMatrix& V);
        void setb(CRBMMatrix& b);
        void setc(CRBMMatrix& c);

        const CRBMMatrix& z() { return _z; }
        void  initLearning(int n);

        int bins() {return _bins;};


      private:

        double __sigm(double v);

        int    _n;            // number of output units
        int    _m;            // number of hidden units
        int    _k;            // number of input units
        int    _uditerations; // number of up-down iterations
        int    _bins;

        CRBMMatrix _W;            // interaction weights between hidden and outputs
        CRBMMatrix _Wt;           // transposed W
        CRBMMatrix _V;            // interaction weights between hidden and inputs
        CRBMMatrix _b;            // bias values for output
        CRBMMatrix _c;            // bias values for hidden

        CRBMMatrix _z;
    };
  }
}

#endif // __CRBM_H__

