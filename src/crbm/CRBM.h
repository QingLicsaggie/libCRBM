#ifndef __CRBM_H__
#define __CRBM_H__

#include <matrix/Matrix.h>
#include <crbm/RBM.h>

namespace libcrbm
{
  namespace binary
  {
    class CRBM : public RBM
    {
      public:

        CRBM(int n, int m, int k);
        ~CRBM();

        void learn(Matrix& x, Matrix& y);
        void control(Matrix& x, Matrix& y);

      private:

        void __up(Matrix& y, Matrix& x);
        void __down(Matrix& z);

        Matrix _x; // input
        Matrix _y; // hidden
        Matrix _z; // output

    };
  }
}

#endif // __CRBM_H__

