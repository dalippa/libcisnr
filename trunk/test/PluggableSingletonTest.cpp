#include "PluggableSingletonTest.h"
#include "PluggableSingleton.h"
#include "SingletonClasses.h"

using CppUnit::TestCase;

MakePluggableSingleton(FromHeader);
MakePluggableSingleton(FromCpp);

PluggableSingletonTest::PluggableSingletonTest() :
  TestCase(typeid(this).name())
{
}

void PluggableSingletonTest::setUp()
{
}

void PluggableSingletonTest::tearDown()
{
}

void PluggableSingletonTest::testSingleton()
{
  const FromHeader& FH(PluggableSingleton<FromHeader, false>::getInstance());
  int value = FH.getValue();
  CPPUNIT_ASSERT_EQUAL(value, 10);

  value = PluggableSingleton<FromCpp, true>::getInstance().getValue();
  CPPUNIT_ASSERT_EQUAL(value, 20);
}

CppUnit::Test* PluggableSingletonTest::suite()
{
  std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
  ts->addTest(new CppUnit::TestCaller<PluggableSingletonTest>("testMult", &PluggableSingletonTest::testSingleton));

  return ts.release();
}
