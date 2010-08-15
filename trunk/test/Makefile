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
TEST_OBJS = $(OBJS) PluggableSingletonTest.o EnumTests.o
OBJ_LIB = $(APP)_unittests
OBJ_LIB_FILE = lib$(OBJ_LIB).a

INCLUDES = -I../include -I.
LIBS = -static -L../lib -L../test -l$(APP) -l$(OBJ_LIB) -lcppunit -l$(OBJ_LIB)
TEST_APP = UnitTests
MAIN = TestMain.cpp

ifeq ($(COVERAGE), 1)
GENINFO = geninfo --no-checksum --output-filename coverage.tmp .
HTML_REPORT = mkdir html_report
GEN_HTML = genhtml -o ./html_report coverage.tmp
else
GENINFO = true
HTML_REPORT = true
GEN_HTML = true
endif

test: clean depend testlib
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(MAIN) -o $(TEST_APP) $(LIBS)

testlib: $(TEST_OBJS)
	ar crv $(OBJ_LIB_FILE) $(TEST_OBJS)

clean:
	@rm -f ./$(TEST_APP) *.o *~
	@rm -f *.gcov *.gcno *.gcda
	@rm -rf html_report coverage.tmp $(OBJ_LIB_FILE)

runtest: test
	@./$(TEST_APP)
	@$(COVERAGE_APP) $(COVERAGE_FLAGS) $(MAIN)
	@$(GENINFO)
	@$(HTML_REPORT)
	@$(GEN_HTML)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<

.cpp.o:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
#	$(COVERAGE_APP) $(COVERAGE_FLAGS) $<

depend:
	@$(MAKEDEPEND) $(INCLUDES)

# DO NOT DELETE
