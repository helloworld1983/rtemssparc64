## $Id: Makefile.am,v 1.6 2009/12/14 18:28:02 joel Exp $

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../../../testsuites/automake/compile.am

include $(top_srcdir)/ada.am

AM_ADAFLAGS += -I$(srcdir)/..

noinst_PROGRAMS = mp07_ada_mp07_node1
mp07_ada_mp07_node1_SOURCES = mp07_node1.adb ../mptest.adb config.h
mp07_ada_mp07_node1_SOURCES += ../mptest.ads
mp07_ada_mp07_node1_SOURCES += ../../../support/init.c

mp07_ada_mp07_node1$(EXEEXT): mp07_node1.adb ../mptest.adb init.$(OBJEXT)
	$(GNATCOMPILE) -margs -a $< -o $@

scndir = $(rtems_ada_testsdir)
dist_scn_DATA = ada_mp07-node1.scn

include $(top_srcdir)/../../../testsuites/automake/local.am
