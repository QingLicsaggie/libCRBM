#include "crbm_test.h"

#include <crbm/CRBM.h>

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace libcrbm::binary;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( crbmTest );

void crbmTest::testInit()
{
  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k, m, n, 10);

  CPPUNIT_ASSERT_EQUAL(n, crbm->n());
  CPPUNIT_ASSERT_EQUAL(m, crbm->m());
  CPPUNIT_ASSERT_EQUAL(k, crbm->k());

  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, crbm->W(a,b), 0.000001);
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, crbm->V(a,c), 0.000001);
    }
  }

  for(int a = 0; a < n; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, crbm->b(a), 0.000001);
  }

  for(int a = 0; a < m; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, crbm->c(a), 0.000001);
  }
}

void crbmTest::testRandomInit()
{
  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k,m,n,10);

  crbm->initRandomWeights();
  crbm->initHiddenBiasValues();
  crbm->initInputBiasValues();

  double sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      sum += fabs(crbm->W(a,b));
    }
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      sum += fabs(crbm->V(a,c));
    }
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < n; a++)
  {
    sum += fabs(crbm->b(a));
  }
  CPPUNIT_ASSERT(sum  > 0.000001);

  sum = 0.0;
  for(int a = 0; a < m; a++)
  {
    sum += fabs(crbm->c(a));
  }
  CPPUNIT_ASSERT(sum  > 0.000001);
}

void crbmTest::testUp()
{
  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k,m,n,10);

  crbm->initRandomWeights();
  crbm->initHiddenBiasValues();
  crbm->initInputBiasValues();

  Matrix y = crbm->y();
  Matrix x = crbm->x();

  crbm->up(y, x);
}

void crbmTest::testDown()
{
  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k,m,n,10);

  crbm->initRandomWeights();
  crbm->initHiddenBiasValues();
  crbm->initInputBiasValues();

  Matrix z = crbm->z();

  crbm->down(z);
}
