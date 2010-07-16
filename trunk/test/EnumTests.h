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

using namespace std;

enum MyType { David = 0, Katherine, UNKNOWN_MyType };
RegisterEnum( MyType, UNKNOWN_MyType, David, Katherine );

enum MyType2 { UNKNOWN_MyType2, DavidLippa, KatherineLippa };
RegisterEnum(MyType2, UNKNOWN_MyType2, DavidLippa, KatherineLippa );

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

  void testEnumConversion()
  {
    MyType tt = David;
    MyType2 tt2 = DavidLippa;

    const EnumConverter<MyType, false>& conv(EnumConverter<MyType, false>::getInstance());
    std::cerr << conv.toString(tt) << std::endl;

    const EnumConverter<MyType2, false>& conv2 = EnumConverter<MyType2, false>::getInstance();
    std::cerr << conv2.toString(tt2) << std::endl;

    conv.dumpAll();
    conv2.dumpAll();
  }

  static CppUnit::Test* suite()
  {
    std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
    ADDTEST(ts, EnumTests, testEnumConversion);

    return ts.release();
  }
};

#endif
