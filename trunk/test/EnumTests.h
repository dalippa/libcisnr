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

    const EnumConverter<MyType, false>& conv = 
     EnumConverter<MyType, false>::getInstance();

    const std::string& tt_str(conv.toString(tt));
    CPPUNIT_ASSERT(tt_str == "David");
    CPPUNIT_ASSERT_EQUAL(tt, conv.toEnum(tt_str));
    CPPUNIT_ASSERT_EQUAL(std::string(conv.toString(static_cast<MyType>(-100))),
                         std::string("UNKNOWN_MyType"));
    CPPUNIT_ASSERT_EQUAL(conv.toEnum("GobbledyGook"), UNKNOWN_MyType);

    const EnumConverter<MyType2, false>& conv2 =
     EnumConverter<MyType2, false>::getInstance();
    CPPUNIT_ASSERT_EQUAL(std::string(conv2.toString(tt2)), std::string("DavidLippa"));

    const EnumConverter<MyType2, true>& throwConv =
     EnumConverter<MyType2, true>::getInstance();

    try
    {      
      // try the same thing with a throwing version
      const std::string& tt_str2 = throwConv.toString(tt2);
      CPPUNIT_ASSERT_EQUAL(tt_str2, std::string("DavidLippa"));
      // invert and ensure it works
      CPPUNIT_ASSERT_EQUAL(tt2, throwConv.toEnum(tt_str2));

      // now cause a failure by using garbage; don't care about return
      throwConv.toEnum("IDon'tExist");
      CPPUNIT_ASSERT(false);
    }
    catch(const std::invalid_argument&)
    {
      CPPUNIT_ASSERT(true);
    }

    try
    {
      // now cause a failure by using garbage
      throwConv.toString(static_cast<MyType2>(-1000));
      CPPUNIT_ASSERT(false);
    }
    catch(const std::invalid_argument&)
    {
      CPPUNIT_ASSERT(true);
    }

#ifdef DEBUG
    // dumpAll() returns the contents of the maps
    conv.dumpAll();
    conv2.dumpAll();
#endif
  }

  static CppUnit::Test* suite()
  {
    std::auto_ptr<CppUnit::TestSuite> ts(new CppUnit::TestSuite());
    
    ADDTEST(ts, EnumTests, testEnumConversion);

    return ts.release();
  }
};

#endif
