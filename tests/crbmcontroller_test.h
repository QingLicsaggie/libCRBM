
#include <cppunit/extensions/HelperMacros.h>

class crbmcontrollerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(crbmcontrollerTest);
  CPPUNIT_TEST(testUpdate);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testUpdate();

};
