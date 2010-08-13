/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <cppunit/TestAssert.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#define ADDTEST(suite, classname, method) suite->addTest(new CppUnit::TestCaller<classname>(#method, &classname::method));

#include <memory>

#endif
