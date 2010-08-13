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

INCLUDES = -I../include -I.
LIBS = -static -L../lib -l$(APP) -lcppunit
TEST_APP = UnitTests
MAIN = TestMain.cpp

test: clean depend $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(MAIN) -o $(TEST_APP) $(TEST_OBJS) $(LIBS)

clean:
	@rm -f ./$(TEST_APP) *.o *~
	@rm -f *.gcov *.gcno *.gcda
	@rm -rf html_report coverage.tmp

runtest: test
	@./$(TEST_APP)
	@$(COVERAGE_APP) $(COVERAGE_FLAGS) $(MAIN)
	@geninfo --no-checksum --output-filename coverage.tmp .
	@mkdir html_report
	@genhtml -o ./html_report coverage.tmp

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<

.cpp.o:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
#	$(COVERAGE_APP) $(COVERAGE_FLAGS) $<

depend:
	@$(MAKEDEPEND) $(INCLUDES)

# DO NOT DELETE
