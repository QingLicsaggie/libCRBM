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


void crbmcontrollerTest::testUpdate1()
{
  int bins            = 8;
  int nrOfSensors     = 2;
  int nrOfActuators   = 3;
  int nrOfHiddenUnits = 4;

  CRBMController* crbm = new CRBMController(bins,
                                            nrOfSensors,
                                            nrOfActuators,
                                            nrOfHiddenUnits,
                                            2);

  double sensors[nrOfSensors];
  double actuators[nrOfActuators];

  for(int i = 0; i < nrOfSensors; i++)
  {
    sensors[i] = 2.0 * Random::unit() - 1.0;
  }

  for(int i = 0; i < nrOfActuators; i++)
  {
    actuators[i]  = 2.0 * Random::unit() - 1.0;
  }

  for(int i = 0; i < 5000; i++)
  {
    // cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << i << endl;
    crbm->update(sensors, actuators);
    // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << i << endl;
  }
}

void crbmcontrollerTest::testUpdate2()
{
  for(int runs = 0; runs < 10; runs++)
  {
    int bins            = 2 + (int)(Random::unit() * 10);
    int nrOfSensors     = 1 + (int)(Random::unit() * 10);
    int nrOfActuators   = 1 + (int)(Random::unit() * 10);
    int nrOfHiddenUnits = 1 + (int)(Random::unit() * 10);

    // cout << endl;
    // cout << "Bins:             " << bins << endl;
    // cout << "Nr. of Sensors:   " << nrOfSensors << endl;
    // cout << "Nr. of Actuators: " << nrOfActuators << endl;
    // cout << "Nr. of Hidden:    " << nrOfHiddenUnits << endl;


    CRBMController* crbm = new CRBMController(bins,
                                              nrOfSensors,
                                              nrOfActuators,
                                              nrOfHiddenUnits,
                                              2);

    double sensors[nrOfSensors];
    double actuators[nrOfActuators];

    for(int i = 0; i < nrOfSensors; i++)
    {
      sensors[i] = 2.0 * Random::unit() - 1.0;
    }

    for(int i = 0; i < nrOfActuators; i++)
    {
      actuators[i]  = 2.0 * Random::unit() - 1.0;
    }

    for(int i = 0; i < 100; i++)
    {
      // cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << i << endl;
      crbm->update(sensors, actuators);
      // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << i << endl;
    }
  }
}
