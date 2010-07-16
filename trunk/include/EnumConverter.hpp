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

// GENERAL PURPOSE CLASSES - FORCE REGISTRATION.
// If RegisterEnum() is called, then a specialization will be used
template<typename E, bool throws>
 class EnumConverter
{
  EnumConverter()
  {
    throw std::domain_error("This functionality is not implemented unless you register your enums!");
  }
};

// END GENERAL PURPOSE CLASSES

// an EnumConverter cannot be defined for a type unless it has been registered
#ifndef RegisterEnum
#define RegisterEnum(tp, unknown_value, enum_values ...) \
   MakeEnumConverterImpl(tp, unknown_value, #unknown_value, #enum_values, enum_values);
#endif

// MakeEnumConverterImpl uses template specialization to make it work!
#ifndef MakeEnumConverterImpl
#define MakeEnumConverterImpl(tp, unknown_enum_in, unknown_enum_as_str, enum_values_as_string_list, enum_values...) \
/* Class with private c-tor that is owned by EnumConverter that won't throw if the programmer registered */ \
template<bool throws>                                        \
class EnumConverter<tp, throws> : public EnumConverterImpl<tp, throws> \
{ \
  \
  public: \
  \
  /* better to return static references than pointers. one less null check */ \
  static const EnumConverter<tp, throws>& getInstance() { return mConverter; } \
  \
  /* if no registration - this won't compile. Our guarantee that they registered at compile time. */ \
  static EnumConverter<tp, throws> mConverter; \
  \
  private: \
  \
  EnumConverter() : \
    EnumConverterImpl<tp, throws>(unknown_enum_in, unknown_enum_as_str, enum_values_as_string_list, enum_values) \
      {} \
}; \
\
template<bool throws> EnumConverter<tp, throws> EnumConverter<tp, throws>::mConverter;
#endif

#endif
