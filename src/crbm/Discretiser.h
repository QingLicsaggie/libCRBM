#ifndef __DISCRETISER_H__
#define __DISCRETISER_H__

#include <ostream>
// #ifdef __linux__
#include <stdint.h>
// #endif // linux

namespace libcrbm
{
  class Discretiser 
  {
    public:
      Discretiser(int numberOfBins, double d_min, double d_max);
      double   unmap(uint64_t value);
      uint64_t map(double value);

      void binarise(uint64_t value, double* values); // 3 -> 0011, 8 -> 1000

      friend std::ostream& operator<<(std::ostream& str, const Discretiser& d)
      {
        for(int i = 0; i < d._numberOfBins; i++)
        {
          str << "Bin " << i << " [" << (d._min + i * d._factor) << ", " << (d._min + (i+1) * d._factor) << "]" << std::endl;
        }
        return str;
      };

    private:
      double _min;
      double _max;
      double _domain;
      double _factor;
      int    _numberOfBins;
      int    _n;
  };
}
#endif // __DISCRETISER_H__

