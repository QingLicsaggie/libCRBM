#include "crbmcontroller_test.h"

#include <crbm/CRBMController.h>
#include <crbm/Random.h>

#include <iostream>
#include <string>
#include <math.h>
#include <random>

using namespace std;
using namespace libcrbm;
using namespace libcrbm::binary;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( crbmcontrollerTest );


void crbmcontrollerTest::testUpdate()
{
  int bins            = 8;
  int nrOfSensors     = 10;
  int nrOfActuators   = 20;
  int nrOfHiddenUnits = 5;

  CRBMController* crbm = new CRBMController(bins, nrOfSensors, nrOfActuators, nrOfHiddenUnits);

  double sensors[nrOfSensors];
  double actuators[nrOfActuators];
  double actuators2[nrOfActuators];

  for(int i = 0; i < nrOfSensors; i++)
  {
    sensors[i] = 2.0 * Random::unit() - 1.0;
  }

  for(int i = 0; i < nrOfActuators; i++)
  {
    actuators[i]  = 2.0 * Random::unit() - 1.0;
    actuators2[i] = actuators[1];
  }

  int n = ((int)ceil(log2(bins)) * nrOfSensors);
  int k = ((int)ceil(log2(bins)) * nrOfActuators);
  int m = nrOfHiddenUnits;

  Matrix W(m,n);
  Matrix V(m,k);
  Matrix b(n,1);
  Matrix c(m,1);

  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      W(i,j) = Random::unit();
    }
  }

  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < k; j++)
    {
      V(i,j) = Random::unit();
    }
  }

  for(int i = 0; i < n; i++)
  {
    b(i,0) = Random::unit();
  }

  for(int i = 0; i < m; i++)
  {
    c(i,0) = Random::unit();
  }

  crbm->setW(W);
  crbm->setV(V);
  crbm->setb(b);
  crbm->setc(c);

  for(int i = 0; i < 100; i++)
  {
    crbm->update(sensors, actuators);
    for(int j = 0; j < nrOfActuators; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, fabs(actuators[i] - actuators2[i]), 0.00000001);
    }
  }
}

