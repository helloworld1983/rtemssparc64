## $Id: Makefile.am,v 1.10 2009/12/14 18:28:02 joel Exp $

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../../../testsuites/automake/compile.am

include $(top_srcdir)/ada.am

AM_ADAFLAGS += -I$(srcdir)/..

if EXPADA
noinst_PROGRAMS = ada_base_mp_node2
ada_base_mp_node2_SOURCES = mptest-per_node_configuration.adb
endif

ada_base_mp_node2$(EXEEXT): ../mptest.adb init.o
	$(GNATCOMPILE) -margs -a $< -o $@

init.o: ../../../support/init.c
	$(COMPILE.c) -DNODE_NUMBER=2 -I$(srcdir)/.. -c $<

scndir = $(rtems_ada_testsdir)
dist_scn_DATA = ada_base_mp-node2.scn

include $(top_srcdir)/../../../testsuites/automake/local.am
