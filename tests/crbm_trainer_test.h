
#include <cppunit/extensions/HelperMacros.h>

class crbmTrainerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(crbmTrainerTest);
  CPPUNIT_TEST(testTrain);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testTrain();

};
