#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <glog/logging.h>

#include <math.h>
#include <iostream>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

CRBM::CRBM(int n, int m, int k)
  : RBM(n, m, k), _x(n,1), _y(k,1), _z(1,m)
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

void CRBM::__up(Matrix& x, Matrix& y)
{
  // cout << "V:" << _V << endl;
  // cout << "W:" << _W << endl;
  // cout << "b:" << _b << endl;
  // cout << "c:" << _c << endl;
  // cout << "x:" <<  x << endl;
  // cout << "y:" <<  y << endl;
  // cout << "z:" << _z << endl;

  _W * x;

  _z = _c + _V * y + _W * x;
  for(int i = 0; i < _m; i++)
  {
    _z(i,0) = sigm(_z(i,0));
  }
  for(int i = 0; i < _m; i++)
  {
    _z(i,0) = (Random::unit() > _z(i,0))?1.0:0.0;
  }
}

void CRBM::__down(Matrix& z)
{
  _x = _b + _Wt * z;
  for(int i = 0; i < _n; i++)
  {
    _x(i, 0) = sigm(_x(i,0));
  }
  for(int i = 0; i < _n; i++)
  {
    _x(i, 0) = (Random::unit() > _x(i, 0))?1.0:0.0;
  }
}
