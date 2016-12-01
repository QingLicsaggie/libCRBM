#include <crbm/RBM.h>

#include <random>
#include <math.h>

using namespace libcrbm;

RBM::RBM(int n, int m, int k, int uditerations)
  :  _W(m,n), _V(m,k), _b(n,1), _c(m,1), _Wt(n,m)
{
  _n            = n;
  _m            = m;
  _k            = k;
  _uditerations = uditerations;
}

void RBM::initRandomWeights(double w)
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

void RBM::initInputBiasValues(double b)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, b);

  for(int r = 0; r < _b.rows(); r++)
  {
    _b(r,0) = distribution(generator);
  }
}

void RBM::initHiddenBiasValues(double c)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, c);

  for(int r = 0; r < _c.rows(); r++)
  {
    _c(r,0) = distribution(generator);
  }

}

double RBM::sigm(double v)
{
  return 1.0 / (1.0 + exp(-v));
}

void RBM::setW(Matrix W)
{
  _W  = W;
  _Wt = W;
  _Wt.transpose();
}

void RBM::setV(Matrix V)
{
  _V = V;
}

void RBM::setb(Matrix b)
{
  _b = b;
}

void RBM::setc(Matrix c)
{
  _c = c;
}

