#include "crbm_test.h"

#include <crbm/CRBM.h>
#include <crbm/Random.h>

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

  CRBM* crbm = new CRBM(k, m, n, 10, 2);

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

  CRBM* crbm = new CRBM(k,m,n,10, 2);

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
  Random::initialise(false);

  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k,m,n,10,2);

  crbm->initRandomWeights();
  crbm->initHiddenBiasValues();
  crbm->initInputBiasValues();

  Matrix y(k,1);
  Matrix x(n,1);
  for(int i = 0; i < n; i++)
  {
    x(i,0) = Random::unit();
  }
  crbm->up(y, x);
  Matrix z = crbm->z();
  for(int i = 0; i < m; i++)
  {
    CPPUNIT_ASSERT(z(i,0) == 0 || z(i,0) == 1);
  }
}

void crbmTest::testDown()
{
  int n = 10;
  int m = 20;
  int k = 30;

  CRBM* crbm = new CRBM(k,m,n,10,2);

  crbm->initRandomWeights();
  crbm->initHiddenBiasValues();
  crbm->initInputBiasValues();

  Matrix z = crbm->z();
  Matrix x(n,1);
  for(int i = 0; i < n; i++)
  {
    x(i,0) = Random::unit();
  }
  cout << "z: " << z.rows() << ", " << z.cols() << endl;
  crbm->down(z,x);
  for(int i = 0; i < n; i++)
  {
    CPPUNIT_ASSERT(x(i,0) == 0 || x(i,0) == 1);
  }
}

void crbmTest::testGetSet()
{
  int n     = 10;
  int m     = 20;
  int k     = 30;
  int index = 0;

  CRBM* crbm = new CRBM(k,m,n,10,2);
  Matrix W = crbm->W();
  Matrix V = crbm->V();
  Matrix b = crbm->b();
  Matrix c = crbm->c();

  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, W(a,b), 0.000001);
      W(a,b) = index++;
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, V(a,c), 0.000001);
      V(a,c) = index++;
    }
  }

  for(int a = 0; a < n; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, b(a,0), 0.000001);
    b(a,0) = index++;
  }

  for(int a = 0; a < m; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, c(a,0), 0.000001);
    c(a,0) = index++;
  }

  crbm->setW(W);
  crbm->setV(V);
  crbm->setb(b);
  crbm->setc(c);

  W = crbm->W();
  V = crbm->V();
  b = crbm->b();
  c = crbm->c();

  index = 0;
  for(int a = 0; a < m; a++)
  {
    for(int b = 0; b < n; b++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(index,   W(a,b),       0.000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(index++, crbm->W(a,b), 0.000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(W(a,b),  crbm->W(a,b), 0.000001);
    }
  }

  for(int a = 0; a < m; a++)
  {
    for(int c = 0; c < k; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(index,   V(a,c),       0.000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(index++, crbm->V(a,c), 0.000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(V(a,c),  crbm->V(a,c), 0.000001);
    }
  }

  for(int a = 0; a < n; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(index,   b(a,0),     0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(index++, crbm->b(a), 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(b(a,0),  crbm->b(a), 0.000001);
  }

  for(int a = 0; a < m; a++)
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(index,   c(a,0),     0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(index++, crbm->c(a), 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(c(a,0),  crbm->c(a), 0.000001);
  }
}

void crbmTest::testTrain()
{
  int data_points   = 200;
  int n             = 50;
  double step_width = (double)n;

  double sin_points[n+1];
  double cos_points[n+1];

  double** S = new double*[data_points];
  for(int i = 0; i < data_points; i++)
  {
    S[i] = new double[12];
  }

  for(int i = 0; i < n+1; i++)
  {
    sin_points[i] = sin(-M_PI + (double)i * 2.0 * M_PI/step_width);
    cos_points[i] = cos(-M_PI + (double)i * 2.0 * M_PI/step_width);
  }

  for(int i = 0; i < data_points; i++)
  {
    int j = (i + n) % (n+1);
    int k = ((int)(i + 1.5 * ((double)n))) % (n+1);

    S[i][0 ] = sin_points[j];
    S[i][1 ] = cos_points[j];
    S[i][2 ] = sin_points[k];
    S[i][3 ] = cos_points[k];
    S[i][4 ] = sin_points[k];
    S[i][5 ] = cos_points[k];
    S[i][6 ] = sin_points[j];
    S[i][7 ] = cos_points[j];
    S[i][8 ] = sin_points[j];
    S[i][9 ] = cos_points[j];
    S[i][10] = sin_points[k];
    S[i][11] = cos_points[k];

  }

  cout << endl << endl;
  for(int i = 0; i < data_points; i++)
  {
    for(int j = 0; j < 11; j++)
    {
      cout << S[i][j] << ",";
    }
    cout << S[i][11] << endl;
  }
}
