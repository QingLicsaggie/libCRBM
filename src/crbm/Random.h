#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{
  public:
    static void   initialise();
    static double unit();
    static int    rand(int min, int max);
};

#endif // __RANDOM_H__
