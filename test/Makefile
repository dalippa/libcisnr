#
# The information in this file is
# Copyright(c) David Lippa (dalippa@gmail.com)
# and is subject to the terms and conditions of the
# GNU Lesser General Public License Version 2.1
# The license text is available from   
# http://www.gnu.org/licenses/lgpl.html
#
MAKEDEPEND = makedepend

APP = cisnr

OBJS = SingletonClasses.o
TEST_OBJS = $(OBJS) PluggableSingletonTest.o

CXXFLAGS = -g -Wall -DDEBUG
CFLAGS = -g -Wall -std=c99 -DDEBUG
INCLUDES = -I../include -I.
LIBS = -static -L../lib -l$(APP) -lcppunit
TEST_APP = UnitTests

test: clean depend $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) TestMain.cpp -o $(TEST_APP) $(TEST_OBJS) $(LIBS)

clean:
	rm -f ./$(TEST_APP) *.o *~

runtest: test
	./$(TEST_APP)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

depend:
	$(MAKEDEPEND) $(INCLUDES)

# DO NOT DELETE
