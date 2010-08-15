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
#ifndef ENUM_CONVERTER_IMPL_H
#define ENUM_CONVERTER_IMPL_H

#include <stdarg.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <map>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif

/**
 * In the current implementation, the Controller is a Singleton.
 * In the future, if one can declare an EnumConverter not as a Singleton,
 * that class must provide a means of determining whether to throw on not found.
 *
 * Controller is some class in the derived hierarchy that handles the instance
 * variable of whether this class throws. Has to be an instance variable
 * since we don't want to have 2 converters, one for throwing and one for not -
 * or worse yet, have the nothrow version catch the exception of the throwing one.
 * That would be too slow. This is more "Java-style" - implementing a contract
 * via an interface.
 */
template<typename E, typename Controller>
class EnumConverterImpl
{
  public:
#ifdef DEBUG

  void dumpAll() const {
    for (typename StringToType::const_iterator ci = stt.begin(); ci != stt.end(); ++ci)
    {
      std::cerr << ci->first << std::endl;
    }
  }
#endif

  const char* const toString(E t) const {             
    typename TypeToString::const_iterator found = tts.find(t); 
    if (found != tts.end()) return &(found->second)[0]; 
    // FIXME: temporary - controllers are read-only for EnumConverterImpl
    if (dynamic_cast<const Controller* const>(this)->throwsOnNotFound()) // defined in subclass
      throw std::invalid_argument(std::string(typeid(E).name()) + " was not properly registered!"); 
    return unknown_enum_string.c_str(); 
  } 
   
  E toEnum(const std::string& str) const {           
    typename StringToType::const_iterator found = stt.find(str);       
    if (found != stt.end()) return found->second;
    if (dynamic_cast<const Controller* const>(this)->throwsOnNotFound()) // defined in subclass
      throw std::invalid_argument(std::string(typeid(E).name()) + " was not properly registered!"); 
    return unknown_enum; 
  } 

  virtual ~EnumConverterImpl() {}
  
  protected: 
  // arrays are guaranteed = in size by way of how they are created with macros
  EnumConverterImpl(E unk, const std::string& unk_as_str, const std::string& values_as_comma_sep_list, E en, ...) : 
  unknown_enum_string(unk_as_str), unknown_enum(unk) 
  { 
    std::vector<std::string> splat;
    boost::split( splat, values_as_comma_sep_list, boost::algorithm::is_any_of(",") );
    
    registerEnum(unk, boost::algorithm::trim_copy(unk_as_str));

    va_list ap;
    va_start(ap, en);
    for (std::vector<std::string>::const_iterator i = splat.begin(); i != splat.end(); ++i)
    {
      registerEnum(en, boost::algorithm::trim_copy(*i));
      en = (E) va_arg(ap, int);
    }
  }

  private:  
  typedef std::map<std::string, E> StringToType;
  typedef std::map<E, std::string> TypeToString;
   
  StringToType stt;
  TypeToString tts;
  
  void registerEnum(const E& e, const std::string& str)
  {
    tts.insert(typename TypeToString::value_type(e, str));
    stt.insert(typename StringToType::value_type(str, e));
  }

  const std::string unknown_enum_string;
  const E unknown_enum;
};

#endif
