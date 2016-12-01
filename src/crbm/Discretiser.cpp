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
  _n            = (int)ceil(log2(_numberOfBins));
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

void Discretiser::binarise(uint64_t value, double* values, int n)
{
  for(int i = 0; i < n; i++)
  {
    if(((1 << i) & value) > 0)
    {
      values[i] = 1.0;
    }
    else
    {
      values[i] = 0.0;
    }
  }
} 

double Discretiser::unbinarise(double* values, int n)
{
  double v = 0.0;
  for(int i = 0; i < n; i++) if(values[i] > 0) v += (1 << i);
  return v;
}

void Discretiser::double2doublearray(double value, double *values)
{
  binarise(map(value), values, _n);
}

double Discretiser::doublearray2double(double *values)
{
  return unmap(unbinarise(values, _n));
}

