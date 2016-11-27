
#include <cppunit/extensions/HelperMacros.h>

class rbmTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(rbmTest);
  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testRandomInit);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testInit();
    void testRandomInit();

};
