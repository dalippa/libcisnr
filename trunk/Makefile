/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
MAKEDEPEND = makedepend

OBJS = 
TEST_OBJS = TestMain.o

CXXFLAGS = -g -Wall -DDEBUG
CFLAGS = -g -Wall -std=c99 -DDEBUG
INCLUDES = 
LIBS = -static -L. -l$(APP) -lcppunit
TEST_APP = UnitTests

lib:
	make -C src

clean:
	make -C src clean
	@rm TAGS
	@~/work/dotags

runtest: clean
	make -C src
	make -C test runtest
