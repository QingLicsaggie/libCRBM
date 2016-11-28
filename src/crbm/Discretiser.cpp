#include "Discretiser.h"

#include <iostream>
#include <math.h>

#define MIN(a,b) ((a<b)?a:b)

using namespace std;
using namespace libcrbm;

Discretiser::Discretiser(int numberOfBins, double d_min, double d_max)
{
  _numberOfBins = numberOfBins;
  _min          = d_min;
  _max          = d_max;
  _domain       = d_max - d_min;
  _factor       = _domain / ((double)numberOfBins);

  double d = log2(_numberOfBins);
  _n = (int)d;
  if(fabs(d - log2(_numberOfBins)) > 0.00001) _n++;
}


uint64_t Discretiser::map(double value)
{
  double f = ((value - _min) / _domain);
  // cout << value << " " << MIN((uint64_t)(f * _numberOfBins), _numberOfBins - 1) << endl;
  return MIN((uint64_t)(f * _numberOfBins), _numberOfBins - 1);
}

double Discretiser::unmap(uint64_t value)
{
  return _min + 0.5 * _factor + ((double)value) * _factor;
}

void Discretiser::binarise(uint64_t value, double* values)
{
  int v = 1;
  for(int i = 0; i < _n; i++)
  {
    if(((v << i) & value) > 0)
    {
      values[i] = 1.0;
    }
    else
    {
      values[i] = 0.0;
    }
  }
} 
