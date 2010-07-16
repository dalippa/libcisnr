/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef SWITCH_H
#define SWITCH_H

#include "EnumConverter.hpp"

#include <map>
#include <typeinfo>

// ==== BASE ACTIONS - 'Action' is the basis of actions that don't throw
template<typename E>
struct Action
{
  virtual ~Action() {}
  virtual void operator()(const E& incoming) = 0;
};
  
template<typename E>
struct ActionImpl : Action<E>
{
  virtual void operator()(const E& incoming) {}
};

// ==== 'ThrowAction' is the basis of any actions that throw
template<typename E>
struct ThrowActionImpl : ActionImpl<E>
{
  void operator()(const E& incoming) {
    std::stringstream strm;
    strm << "No action is registered with the incoming enum of type '"
         << typeid(E).name() << "' with value = '" << incoming << "'!" << std::endl;
    throw std::logic_error(strm.str());
  }
};

// ================================================================================

template<typename E, template<typename _en> class DefaultActionImpl = ActionImpl>
 class SwitchOnEnum
{
  typedef DefaultActionImpl<E> ActionType;
  typedef std::map<E, Action<E>* const> ActionMap;

  ActionMap mActions;
  ActionType defaultA;

  public:  
  ~SwitchOnEnum()
  {
    for (typename ActionMap::iterator i = mActions.begin(); i != mActions.end(); ++i) {
      delete i->second;
    } 
  }

  SwitchOnEnum<E, DefaultActionImpl>& registerAction(const E& cause, std::auto_ptr<ActionType> effect)
  {
    mActions.insert(ActionMap::value_type(cause, effect.release()));
    return *this;
  } 

  // take ownership of a bare pointer for simplicity
  SwitchOnEnum<E, DefaultActionImpl>& registerAction(const E& cause, ActionType* const effect) {
    mActions.insert(typename ActionMap::value_type(cause, effect));
    return *this;
  } 
 
  void operator()(const E& incoming) {
    typename ActionMap::const_iterator ci = mActions.find(incoming);
    if (ci != mActions.end()) (*ci->second)(incoming); 
    else defaultA(incoming);
  }
};

enum EncodingType { INT1SBYTE = 0, INT1UBYTE, UNKNOWN_EncodingType };
RegisterEnum( EncodingType, UNKNOWN_EncodingType, INT1SBYTE, INT1UBYTE );

#endif
