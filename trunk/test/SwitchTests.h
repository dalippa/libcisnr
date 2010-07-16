/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef SWITCH_TESTS_H
#define SWITCH_TESTS_H

#include "TestCommon.h"
#include "SwitchOnEnum.hpp"

#include <memory>

class SwitchTests : public CppUnit::TestCase
{
  public:

  SwitchTests() : TestCase("SwitchTests") {}

  void setUp()
  {
  }

  void tearDown()
  {
  }

  void testSwitchAlg()
  {
    SwitchOnEnum<EncodingType> alg;
    alg.registerAction(INT1SBYTE, new ThrowActionImpl<EncodingType>()).
     registerAction(INT1UBYTE, new ActionImpl<EncodingType>());

    try
    {
      alg(INT1SBYTE);
      CPPUNIT_ASSERT(false); // this should throw
    }
    catch(std::exception& e)
    {
      CPPUNIT_ASSERT(true);
    }
    alg(INT1UBYTE);
    CPPUNIT_ASSERT(true);
  }

  static CppUnit::Test* suite()
  {
    std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
    ADDTEST(ts, SwitchTests, testSwitchAlg);

    return ts.release();
  }
};

#endif
