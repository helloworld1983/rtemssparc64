##
##  $Id: Makefile.am,v 1.16 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = cxx_iostream
cxx_iostream_SOURCES = init.cc system.h

dist_rtems_tests_DATA = iostream.scn
dist_rtems_tests_DATA += iostream.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

cxx_iostream_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(cxx_iostream_OBJECTS) $(cxx_iostream_LDADD)
LINK_LIBS = $(cxx_iostream_LDLIBS)

cxx_iostream$(EXEEXT): $(cxx_iostream_OBJECTS) $(cxx_iostream_DEPENDENCIES)
	@rm -f cxx_iostream$(EXEEXT)
	$(make-cxx-exe)

include $(top_srcdir)/../automake/local.am
