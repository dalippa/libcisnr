#
# The information in this file is
# Copyright(c) David Lippa (dalippa@gmail.com)
# and is subject to the terms and conditions of the
# GNU Lesser General Public License Version 2.1
# The license text is available from   
# http://www.gnu.org/licenses/lgpl.html
#
MAKEDEPEND = makedepend
SHELL = /bin/bash

APP = cisnr

LIB_OBJS = dbc.o

INCLUDES = -I../include
LIBS = -static -L. -l$(APP) -lcppunit
TEST_APP = UnitTests
OUT_DIR = ../lib

lib: depend $(LIB_OBJS)
	@ar cq $(OUT_DIR)/lib$(APP).a $(LIB_OBJS)

runtest:

clean:
	@rm -f $(APP) TAGS *.o *~ $(OUT_DIR)/lib$(APP).a
	@rm -f *.gcov *.gcno

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<

.cpp.o:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

depend:
	@$(MAKEDEPEND) $(INCLUDES)

# DO NOT DELETE
