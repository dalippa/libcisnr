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
#ifndef ENUM_CONVERTER_H
#define ENUM_CONVERTER_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

#include "EnumConverterImpl.hpp"
#include "PluggableSingleton.h"

class EnumConverterController
{
   bool _throws;
 public:
   EnumConverterController(bool throws) : _throws(throws) {}
   const bool throwsOnNotFound() const { return _throws; }
};

template<typename E, bool throws_on_error> class EnumConverter
{
  EnumConverter() {}
};

template<typename E, bool throws_on_error> class EnumConverterSingleton
{
  EnumConverterSingleton() {}
};

// an EnumConverter cannot be defined for a type unless it has been registered
#ifndef RegisterEnum
#define RegisterEnum(tp, unknown_value, enum_values ...) \
   MakeEnumConverterImpl(tp, unknown_value, #unknown_value, #enum_values, enum_values);
#endif

// We now can have an EnumConverter that can be declared on the fly anywhere
#ifndef MakeEnumConverterImpl
#define MakeEnumConverterImpl(tp, unknown_enum_in, unknown_enum_as_str, enum_values_as_string_list, enum_values...) \
template<bool throws_on_error> \
class EnumConverter<tp, throws_on_error> : public EnumConverterImpl<tp, EnumConverterController>, public EnumConverterController { \
  public: \
  EnumConverter() : \
  EnumConverterImpl<tp, EnumConverterController>(unknown_enum_in, unknown_enum_as_str, enum_values_as_string_list, enum_values), \
  EnumConverterController(throws_on_error) {} \
}; \
/* Syntactic sugar is below */ \
/* TODO: Document this 
template<bool throws_on_error> \
class EnumConverterSingleton<tp, throws_on_error> : public PluggableSingleton<EnumConverter<tp, throws_on_error>, false> {}; */
#endif

#endif
