#include "crbmio_test.h"

#include <crbm/CRBM.h>
#include <crbm/CRBMIO.h>

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace libcrbm::binary;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( crbmioTest );

void crbmioTest::testIO()
{
  int n = 10;
  int m = 20;
  int k = 30;

  int index = 0;

  CRBM* crbm = new CRBM(k, m, n, 10, 2);

  CRBMMatrix W = crbm->W();
  CRBMMatrix V = crbm->V();
  CRBMMatrix b = crbm->b();
  CRBMMatrix c = crbm->c();

  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      W(a,b) = index++;
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      V(a,c) = index++;
    }
  }

  for(int a = 0; a < n; a++)
  {
    b(a,0) = index++;
  }

  for(int a = 0; a < m; a++)
  {
    c(a,0) = index++;
  }

  crbm->setW(W);
  crbm->setV(V);
  crbm->setb(b);
  crbm->setc(c);

  CRBMIO::write("/tmp/test.csv", crbm);

  CRBM *test = CRBMIO::read("/tmp/test.csv");

  for(int a = 0; a < n; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(crbm->b(a), test->b(a), 0.000001);
  }

  for(int a = 0; a < m; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(crbm->c(a), test->c(a), 0.000001);
  }

  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(crbm->W(a,b), test->W(a,b), 0.000001);
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(crbm->V(a,c), test->V(a,c), 0.000001);
    }
  }

  CPPUNIT_ASSERT_EQUAL(crbm->uditerations(), test->uditerations());
  CPPUNIT_ASSERT_EQUAL(crbm->n(),            test->n());
  CPPUNIT_ASSERT_EQUAL(crbm->m(),            test->m());
  CPPUNIT_ASSERT_EQUAL(crbm->k(),            test->k());
}
