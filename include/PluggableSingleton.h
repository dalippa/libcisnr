/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef PLUGGABLE_SINGLETON_H
#define PLUGGABLE_SINGLETON_H

/**
 *
 * Usage: declare this with your class to make it a Singleton.
 * Then, in the CPP file for your class, define the static variable
 */
template<typename M, bool global_writable>
class PluggableSingleton
{
  PluggableSingleton() {}
};

#ifndef MakePluggableSingleton
#define MakePluggableSingleton(TP) \
template<> class PluggableSingleton<TP, true> : public TP    \
{ \
  static PluggableSingleton<TP, true> _s;            \
  public: \
  static PluggableSingleton<TP, true>& getInstance() { return _s; } \
};\
template<> class PluggableSingleton<TP, false> : public TP    \
{ \
  static PluggableSingleton<TP, false> _s;            \
  public: \
  static const PluggableSingleton<TP, false>& getInstance() { return _s; }    \
};

#endif

#endif
