#include <crbm/Random.h>

#include <stdlib.h>

#include <iostream>

using namespace std;

void Random::initialise()
{
  time_t t;
  time(&t);
  srand48(t);
}

double Random::unit()
{
  return drand48();
}

int Random::rand(int min, int max)
{
  return min + int(drand48() * (double)max + 0.5);
}
