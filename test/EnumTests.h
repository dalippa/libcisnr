/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 *
 * This work was inspired by postings related to boost::assign
 * and the StringUtilities library of the Opticks project
 * (http://opticks.org).
 */
#ifndef ENUM_TESTS_H
#define ENUM_TESTS_H

#include "EnumConverter.hpp"

#include "TestCommon.h"

#include <iostream>
#include <memory>
#include <typeinfo>

// register one in the header file
enum MyType { David = 0, Katherine, UNKNOWN_MyType };
RegisterEnum( MyType, UNKNOWN_MyType, David, Katherine );

class EnumTests : public CppUnit::TestCase
{
 public:
  EnumTests() : TestCase(typeid(this).name()) {}

  void setUp()
  {
  }

  void tearDown()
  {
  }

  void testEnumConversion();

  static CppUnit::Test* suite()
  {
    std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
    ADDTEST(ts, EnumTests, testEnumConversion);

    return ts.release();
  }
};

#endif
