
#include <cppunit/extensions/HelperMacros.h>

class discretiserTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(discretiserTest);
  CPPUNIT_TEST(testBinariseValue);
  CPPUNIT_TEST(testUnBinariseValue);
  CPPUNIT_TEST(testBinVetorOfValue);
  CPPUNIT_TEST_SUITE_END();

  public:

    void testBinariseValue();
    void testUnBinariseValue();
    void testBinVetorOfValue();

};
