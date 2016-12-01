
#include <cppunit/extensions/HelperMacros.h>

class crbmcontrollerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(crbmcontrollerTest);
  CPPUNIT_TEST(testUpdate1);
  // CPPUNIT_TEST(testUpdate2);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testUpdate1();
    void testUpdate2();

};
