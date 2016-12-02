#include <cppunit/extensions/HelperMacros.h>

class crbmioTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(crbmioTest);
  CPPUNIT_TEST(testIO);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testIO();

};
