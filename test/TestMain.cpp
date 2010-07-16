/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#include "TestCommon.h"

#include "EnumTests.h"
#include "SwitchTests.h"

#include "AlgTests.h"

#include <cppunit/TextOutputter.h>

using namespace CppUnit;

int main(int argc, const char* argv[])
{
  TestResult controller;
  TestResultCollector trc;
  controller.addListener(&trc);

  TestRunner runner;
  runner.addTest(SwitchTests::suite());
  runner.addTest(EnumTests::suite());
  runner.addTest(AlgTests::suite());
  runner.run(controller);

  TextOutputter to(&trc, std::cerr);
  to.write();
  to.printStatistics();

  return 0;
}
