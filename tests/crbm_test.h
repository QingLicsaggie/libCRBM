
#include <cppunit/extensions/HelperMacros.h>

class crbmTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(crbmTest);
  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testRandomInit);
  CPPUNIT_TEST(testUp);
  CPPUNIT_TEST(testDown);
  CPPUNIT_TEST(testGetSet);
  CPPUNIT_TEST(testTrain);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testInit();
    void testRandomInit();
    void testUp();
    void testDown();
    void testGetSet();
    void testTrain();

};
