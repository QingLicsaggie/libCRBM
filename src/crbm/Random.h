#ifndef __RANDOM_H__
#define __RANDOM_H__

namespace libcrbm
{
  class Random
  {
    public:
      static void   initialise(bool verbose = false);
      static void   initialise(int seed, bool verbose = false);
      static double unit();
      static double rand(double min, double max);
      static int    randi(int min, int max);
  };
}

#endif // __RANDOM_H__
