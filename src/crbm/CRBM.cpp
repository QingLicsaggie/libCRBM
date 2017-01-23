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

CRBM::CRBM(int k, int m, int n, int u, int bins)
  :  _W(m,n), _V(m,k), _Wt(n,m),
     _b(n,1), _c(m,1), _z(m,1)
{
  _k            = k;
  _m            = m;
  _n            = n;
  _uditerations = u;
  _bins         = bins;
}

CRBM::~CRBM()
{ }

void CRBM::initLearning(int n)
{
  Matrix ctmp(_c.rows(), n);
  Matrix btmp(_b.rows(), n);

  for(int r = 0; r < btmp.rows(); r++)
  {
    for(int c = 0; c < n; c++)
    {
      btmp(r,c) = _b(r,0);
    }
  }

  for(int r = 0; r < ctmp.rows(); r++)
  {
    for(int c = 0; c < n; c++)
    {
      ctmp(r,c) = _c(r,0);
    }
  }
  _b = btmp;
  _c = ctmp;
}

void CRBM::learn(Matrix& y, Matrix& x)
{
  // up(y,x);
  for(int i = 0; i < _uditerations; i++)
  {
    down(_z, x);
    up(y, x);
  }
}

void CRBM::control(Matrix& y, Matrix& x)
{
  up(y,x);
  for(int i = 0; i < _uditerations-1; i++)
  {
    down(_z, x);
    up(y, x);
  }
  down(_z, x);
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

  // cout << "size(y) " << y.rows() << ", " << y.cols() << endl;

  _z = _c + _V * y + _W * x;

  for(int r = 0; r < _z.rows(); r++)
  {
    for(int c = 0; c < _z.cols(); c++)
    {
      double rand = Random::unit();
      // cout << "crbm-up: " << rand << endl;
      _z(r,c) = (rand < __sigm(_z(r,c)))?1.0:0.0;
    }
  }
}

void CRBM::down(Matrix& z, Matrix &x)
{
  // cout << "down" << endl;
  // cout << "Wt:" << _Wt << endl;
  // cout << "z:" <<  z << endl;
  // cout << "size b: " << _b.rows() << ", " << _b.cols() << " _Wt: " << _Wt.rows() << ", " << _Wt.cols() << " z.T: " << z.cols() << ", " << z.rows() << endl;

  x = _b + _Wt * z;
  for(int r = 0; r < x.rows(); r++)
  {
    for(int c = 0; c < x.cols(); c++)
    {
      double rand = Random::unit();
      // cout << "crbm-down: " << rand << endl;
      x(r, c) = (rand < __sigm(x(r, c)))?1.0:0.0;
    }
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

  _Wt = _W.T();

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

double CRBM::__sigm(double v)
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

void CRBM::changeb(Matrix& db)
{
  for(int r = 0; r < _b.rows(); r++)
  {
    for(int c = 0; c < _c.cols(); c++)
    {
      _b(r,c) += db(r, c % db.cols());
    }
  }
}

void CRBM::changec(Matrix& dc)
{
  for(int r = 0; r < _c.rows(); r++)
  {
    for(int c = 0; c < _c.cols(); c++)
    {
      _c(r,c) += dc(r, c % dc.cols());
    }
  }
}

void CRBM::changeb(double alpha)
{
  _b *= alpha;
}

void CRBM::changec(double alpha)
{
  _c *= alpha;
}
