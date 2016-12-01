#include "rbm_test.h"

#include <crbm/RBM.h>

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace libcrbm;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( rbmTest );


void rbmTest::testInit()
{
  int n = 10;
  int m = 20;
  int k = 30;

  RBM* rbm = new RBM(n, m, k, 10);

  CPPUNIT_ASSERT_EQUAL(n, rbm->n());
  CPPUNIT_ASSERT_EQUAL(m, rbm->m());
  CPPUNIT_ASSERT_EQUAL(k, rbm->k());

  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rbm->W(a,b), 0.000001);
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rbm->V(a,c), 0.000001);
    }
  }

  for(int a = 0; a < n; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rbm->b(a), 0.000001);
  }

  for(int a = 0; a < m; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rbm->c(a), 0.000001);
  }
}

void rbmTest::testRandomInit()
{
  int n = 10;
  int m = 20;
  int k = 30;

  RBM* rbm = new RBM(n,m,k,10);

  rbm->initRandomWeights();
  rbm->initHiddenBiasValues();
  rbm->initInputBiasValues();

  double sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      sum += fabs(rbm->W(a,b));
    }
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      sum += fabs(rbm->V(a,c));
    }
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < n; a++)
  {
    sum += fabs(rbm->b(a));
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    sum += fabs(rbm->c(a));
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

}


