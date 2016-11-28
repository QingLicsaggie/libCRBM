#include "discretiser_test.h"

#include <crbm/Discretiser.h>

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace libcrbm;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( discretiserTest );


void discretiserTest::testBinariseValue()
{
  Discretiser *d = new Discretiser(8, -1.0, 1.0);

  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-1.0));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.99));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.98));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.97));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.96));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.95));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.94));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.93));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.92));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.91));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.9));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.89));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.88));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.87));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.86));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.85));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.84));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.83));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.82));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.81));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.8));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.79));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.78));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.77));
  CPPUNIT_ASSERT_EQUAL(0, (int)d->map(-0.76));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.75));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.74));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.73));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.72));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.71));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.7));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.69));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.68));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.67));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.66));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.65));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.64));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.63));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.62));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.61));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.6));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.59));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.58));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.57));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.56));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.55));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.54));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.53));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.52));
  CPPUNIT_ASSERT_EQUAL(1, (int)d->map(-0.51));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.5));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.49));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.48));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.47));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.46));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.45));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.44));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.43));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.42));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.41));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.4));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.39));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.38));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.37));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.36));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.35));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.34));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.33));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.32));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.31));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.3));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.29));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.28));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.27));
  CPPUNIT_ASSERT_EQUAL(2, (int)d->map(-0.26));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.25));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.24));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.23));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.22));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.21));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.2));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.19));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.18));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.17));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.16));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.15));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.14));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.13));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.12));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.11));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.1));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.09));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.08));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.07));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.06));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.05));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.04));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.03));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.02));
  CPPUNIT_ASSERT_EQUAL(3, (int)d->map(-0.01));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.0));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.01));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.02));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.03));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.04));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.05));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.06));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.07));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.08));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.09));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.1));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.11));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.12));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.13));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.14));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.15));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.16));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.17));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.18));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.19));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.2));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.21));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.22));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.23));
  CPPUNIT_ASSERT_EQUAL(4, (int)d->map(0.24));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.25));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.26));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.27));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.28));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.29));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.3));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.31));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.32));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.33));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.34));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.35));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.36));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.37));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.38));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.39));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.4));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.41));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.42));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.43));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.44));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.45));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.46));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.47));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.48));
  CPPUNIT_ASSERT_EQUAL(5, (int)d->map(0.49));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.5));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.51));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.52));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.53));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.54));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.55));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.56));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.57));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.58));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.59));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.6));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.61));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.62));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.63));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.64));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.65));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.66));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.67));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.68));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.69));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.7));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.71));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.72));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.73));
  CPPUNIT_ASSERT_EQUAL(6, (int)d->map(0.74));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.75));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.76));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.77));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.78));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.79));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.8));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.81));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.82));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.83));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.84));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.85));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.86));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.87));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.88));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.89));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.9));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.91));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.92));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.93));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.94));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.95));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.96));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.97));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.98));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(0.99));
  CPPUNIT_ASSERT_EQUAL(7, (int)d->map(1.0));

  delete d;
}

void discretiserTest::testUnBinariseValue()
{
  Discretiser *d = new Discretiser(8, -1.0, 1.0);

  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.875, d->unmap(0));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.625, d->unmap(1));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.375, d->unmap(2));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(-0.125, d->unmap(3));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.125, d->unmap(4));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.375, d->unmap(5));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.625, d->unmap(6));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));
  CPPUNIT_ASSERT_EQUAL(0.875, d->unmap(7));

  delete d;
}

void discretiserTest::testBinVetorOfValue()
{
  Discretiser *d = new Discretiser(8, -1.0, 1.0);
  double* v = new double[3];


  d->binarise(0, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[2], 0.000001);


  d->binarise(1, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[2], 0.000001);


  d->binarise(2, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[2], 0.000001);


  d->binarise(3, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[2], 0.000001);


  d->binarise(4, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[2], 0.000001);


  d->binarise(5, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[2], 0.000001);

  d->binarise(6, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[2], 0.000001);

  d->binarise(7, v);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[0], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[1], 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v[2], 0.000001);

  delete d;
}

void discretiserTest::testUnBinVetorOfValue()
{
  Discretiser *d = new Discretiser(8, -1.0, 1.0);
  double* values = new double[3];
  double v       = -1.0;


  values[0] = 0.0; values[1] = 0.0; values[2] = 0.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v, 0.00001);

  values[0] = 1.0; values[1] = 0.0; values[2] = 0.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v, 0.00001);

  values[0] = 0.0; values[1] = 1.0; values[2] = 0.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, v, 0.00001);

  values[0] = 1.0; values[1] = 1.0; values[2] = 0.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, v, 0.00001);

  values[0] = 0.0; values[1] = 0.0; values[2] = 1.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0, v, 0.00001);

  values[0] = 1.0; values[1] = 0.0; values[2] = 1.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, v, 0.00001);

  values[0] = 0.0; values[1] = 1.0; values[2] = 1.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, v, 0.00001);

  values[0] = 1.0; values[1] = 1.0; values[2] = 1.0;
  v = d->unbinarise(values);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(7.0, v, 0.00001);

  delete d;
}
