#
# The information in this file is
# Copyright(c) David Lippa (dalippa@gmail.com)
# and is subject to the terms and conditions of the
# GNU Lesser General Public License Version 2.1
# The license text is available from   
# http://www.gnu.org/licenses/lgpl.html
#
MAKEDEPEND = makedepend

OBJS = 
TEST_OBJS = TestMain.o

CXXFLAGS = -Wall
CFLAGS_BAS = -Wall -std=c99
INCLUDES = 
LIBS = -static -L. -l$(APP) -lcppunit
TEST_APP = UnitTests

ifeq ($(COVERAGE), 1)
CXXFLAGS = -ftest-coverage -fprofile-arcs
CFLAGS = -ftest-coverage -fprofile-arcs
COVERAGE_APP = gcov
COVERAGE_FLAGS =
else
COVERAGE_APP = file
endif

ifeq ($(DEBUG), 1)
CXXFLAGS := "$(CXXFLAGS) -g -DDEBUG"
CFLAGS := "$(CFLAGS) -g -DDEBUG"
else
CXXFLAGS := "$(CXXFLAGS) -O2"
CFLAGS := "$(CFLAGS) -O2"
endif

all:
	@echo Building library...
	@make CFLAGS=$(CFLAGS) CXXFLAGS=$(CXXFLAGS) COVERAGE_APP=$(COVERAGE_APP) COVERAGE_FLAGS=$(COVERAGE_FLAGS) -C src

clean:
	@make -C test clean
	@make -C src clean
	@rm -f TAGS
	@find $(PWD) -name "*.h" -o -name "*.hpp" -o -name "*.cpp" | xargs etags --output=TAGS -

distclean: clean
	@rm -f TAGS

runtest: clean
	@make CFLAGS=$(CFLAGS) CXXFLAGS=$(CXXFLAGS) COVERAGE_APP=$(COVERAGE_APP) COVERAGE_FLAGS=$(COVERAGE_FLAGS) -C src
	@make CFLAGS=$(CFLAGS) CXXFLAGS=$(CXXFLAGS) COVERAGE_APP=$(COVERAGE_APP) COVERAGE_FLAGS=$(COVERAGE_FLAGS) -C test runtest
