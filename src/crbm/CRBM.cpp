#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <glog/logging.h>

#include <math.h>

using namespace libcrbm;
using namespace libcrbm::binary;

CRBM::CRBM(int n, int m, int k)
  : RBM(n, m, k), _x(1,n), _y(1,m), _z(k,0)
{
  Random::initialise();
}

CRBM::~CRBM()
{
}

void CRBM::learn(Matrix& y, Matrix& x)
{
  __up(y,x);
  for(int i = 0; i < _uditerations; i++)
  {
    __down(_z);
    __up(y, _x);
  }
}

void CRBM::control(Matrix& y, Matrix& x)
{
  __up(y,x);
  for(int i = 0; i < _uditerations-1; i++)
  {
    __down(_z);
    __up(y, _x);
  }
  __down(_z);
}


void CRBM::__up(Matrix& y, Matrix& x)
{
  _z = _c + _V * _y + _W * _z;
  for(int i = 0; i < _k; i++)
  {
    _z(i, 0) = (Random::unit() > _z(i, 0))?1.0:0.0;
  }
}

void CRBM::__down(Matrix& z)
{
  _x = _b + _W * _z;
  for(int i = 0; i < _n; i++)
  {
    _x(i, 0) = (Random::unit() > _x(i, 0))?1.0:0.0;
  }
}
