/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef ALGTESTS_H
#define ALGTESTS_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

// Multiply a number - 2 numbers w/out using *
int multiply(int first, int second)
{
  if (first == 0 || second == 0) return 0;

  int mult = 0;
  int firstt = first;
  while (firstt++ < 0)
  {
    mult = mult - second;
  }
  firstt = first;
  while (first-- > 0)
  {
    mult = mult + second;
  }

  return mult;
}

class AlgTests : public CppUnit::TestCase
{
 public:
  AlgTests() : TestCase(typeid(this).name()) {}

  void setUp()
  {
  }

  void tearDown()
  {
  }

  void testMult()
  {
    // +/- matrix - any pos/neg combinations
    CPPUNIT_ASSERT(multiply(-6, 3) == -18);
    CPPUNIT_ASSERT(multiply(-6, -3) == 18);
    CPPUNIT_ASSERT(multiply(6, -3) == -18);
    CPPUNIT_ASSERT(multiply(6, 3) == 18);

    // now for identity properties: 0
    CPPUNIT_ASSERT(multiply(6, 0) == 0);
    CPPUNIT_ASSERT(multiply(0, 3) == 0);
    CPPUNIT_ASSERT(multiply(0, 0) == 0);

    // identity properties: 1
    CPPUNIT_ASSERT(multiply(6, 1) == 6);
    CPPUNIT_ASSERT(multiply(1, 3) == 3);
    CPPUNIT_ASSERT(multiply(1, 1) == 1);
  }

  static CppUnit::Test* suite()
  {
    std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
    ts->addTest(new CppUnit::TestCaller<AlgTests>("testMult", &AlgTests::testMult));

    return ts.release();
  }
};


#endif
