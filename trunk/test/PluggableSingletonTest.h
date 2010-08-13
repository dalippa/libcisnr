/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef PLUGGABLE_SINGLETON_TEST_H
#define PLUGGABLE_SINGLETON_TEST_H

#include "TestCommon.h"

class PluggableSingletonTest : public CppUnit::TestCase
{
 public:
  PluggableSingletonTest();

  void setUp();

  void tearDown();

  void testSingleton();

  static CppUnit::Test* suite();
};

#endif
