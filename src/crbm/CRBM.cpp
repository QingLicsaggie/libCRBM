#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <glog/logging.h>

#include <math.h>
#include <iostream>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

CRBM::CRBM(int n, int m, int k)
  : RBM(n, m, k), _x(n,1), _y(1,m), _z(1,k)
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
  // cout << "c: " << endl << _c << endl;
  // cout << "b: " << endl << _b << endl;
  cout << "W: " << endl << _W << endl;
  // cout << "V: " << endl << _V << endl;
  cout << "x: " << endl << _x << endl;
  // cout << "y: " << endl << _y << endl;
  // cout << "z: " << endl << _z << endl;

  cout << "hier 10 1" << endl;
  _W * _x;
  cout << "hier 10 2" << endl;
  // _V * _y;
  // cout << "hier 10 3" << endl;

  // _z = _c + _y * _V + _z * _W;

  // cout << "hier 10" << endl;
  // for(int i = 0; i < _k; i++)
  // {
    // _z(0, i) = (Random::unit() > _z(0, i))?1.0:0.0;
  // }
  // cout << "hier 11" << endl;
}

void CRBM::__down(Matrix& z)
{
  cout << "hier 12" << endl;
  _x = _b + _z * _W;
  cout << "hier 13" << endl;
  for(int i = 0; i < _n; i++)
  {
    _x(i, 0) = (Random::unit() > _x(i, 0))?1.0:0.0;
  }
  cout << "hier 14" << endl;
}
