#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <glog/logging.h>

#include <math.h>
#include <iostream>
#include <random>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

// k - input
// m - hidden
// n - output

CRBM::CRBM(int k, int m, int n, int u)
  :  _W(m,n), _V(m,k), _b(n,1), _c(m,1), _Wt(n,m), _x(n,1), _y(k,1), _z(m,1)
{
  _k            = k;
  _m            = m;
  _n            = n;
  _uditerations = u;

  Random::initialise();
}

CRBM::~CRBM()
{
}

void CRBM::learn(Matrix& y, Matrix& x)
{
  up(y,x);
  for(int i = 0; i < _uditerations; i++)
  {
    down(_z);
    up(y, _x);
  }
}

void CRBM::control(Matrix& y, Matrix& x)
{
  up(y,x);
  for(int i = 0; i < _uditerations-1; i++)
  {
    down(_z);
    up(y, _x);
  }
  down(_z);
}

void CRBM::up(Matrix& y, Matrix& x)
{
  // cout << "up" << endl;
  // cout << "V:" << _V << endl;
  // cout << "y:" <<  y << endl;
  // _V * y;

  // cout << "W:" << _W << endl;
  // cout << "x:" <<  x << endl;
  // _W * x;

  // cout << "b:" << _b << endl;
  // cout << "c:" << _c << endl;
  // cout << "z:" << _z << endl;

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

void CRBM::down(Matrix& z)
{
  // cout << "down" << endl;
  // cout << "Wt:" << _Wt << endl;
  // cout << "z:" <<  z << endl;
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

void CRBM::initRandomWeights(double w)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, w);

  for(int r = 0; r < _W.rows(); r++)
  {
    for(int c = 0; c < _W.cols(); c++)
    {
      _W(r,c) = distribution(generator);
    }
  }

  for(int r = 0; r < _V.rows(); r++)
  {
    for(int c = 0; c < _V.cols(); c++)
    {
      _V(r,c) = distribution(generator);
    }
  }
}

void CRBM::initInputBiasValues(double b)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, b);

  for(int r = 0; r < _b.rows(); r++)
  {
    _b(r,0) = distribution(generator);
  }
}

void CRBM::initHiddenBiasValues(double c)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, c);

  for(int r = 0; r < _c.rows(); r++)
  {
    _c(r,0) = distribution(generator);
  }

}

double CRBM::sigm(double v)
{
  return 1.0 / (1.0 + exp(-v));
}

void CRBM::setW(Matrix& W)
{
  _W  = W;
  _Wt = W;
  _Wt.transpose();
}

void CRBM::setV(Matrix& V)
{
  _V = V;
}

void CRBM::setb(Matrix& b)
{
  _b = b;
}

void CRBM::setc(Matrix& c)
{
  _c = c;
}

