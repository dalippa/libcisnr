#include "EnumConverter.hpp"
#include "EnumTests.h"

enum MyType2 { UNKNOWN_MyType2, DavidLippa, KatherineLippa };
RegisterEnum(MyType2, UNKNOWN_MyType2, DavidLippa, KatherineLippa );

void EnumTests::testEnumConversion()
{
  MyType tt = David;
  MyType2 tt2 = DavidLippa;

  const EnumConverter<MyType, false> conv;

  const std::string& tt_str(conv.toString(tt));
  CPPUNIT_ASSERT(tt_str == "David");
  CPPUNIT_ASSERT_EQUAL(tt, conv.toEnum(tt_str));
  CPPUNIT_ASSERT_EQUAL(std::string(conv.toString(static_cast<MyType>(-100))),
                       std::string("UNKNOWN_MyType"));
  CPPUNIT_ASSERT_EQUAL(conv.toEnum("GobbledyGook"), UNKNOWN_MyType);

  const EnumConverter<MyType2, false> conv2;
  CPPUNIT_ASSERT_EQUAL(std::string(conv2.toString(tt2)), std::string("DavidLippa"));

  const EnumConverter<MyType2, true> throwConv;

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

  // FIXME: add tests for this
  EnumConverter<MyType, false> ecmt;
}
