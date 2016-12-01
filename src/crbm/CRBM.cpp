#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <glog/logging.h>

#include <math.h>
#include <iostream>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

CRBM::CRBM(int n, int m, int k, int u)
  : RBM(n, m, k, u), _x(n,1), _y(k,1), _z(1,m)
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
  cout << "up" << endl;
  cout << "V:" << _V << endl;
  cout << "y:" <<  y << endl;
  _V * y;

  cout << "W:" << _W << endl;
  cout << "x:" <<  x << endl;
  _W * x;

  cout << "b:" << _b << endl;
  cout << "c:" << _c << endl;
  cout << "z:" << _z << endl;

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
  cout << "down" << endl;
  cout << "Wt:" << _Wt << endl;
  cout << "z:" <<  z << endl;
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
