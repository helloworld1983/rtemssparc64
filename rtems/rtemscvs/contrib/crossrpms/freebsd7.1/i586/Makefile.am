# $Id: Makefile.am,v 1.8 2009/10/21 03:16:11 ralf Exp $

TARGET = i586-pc-freebsd7.1

include $(top_srcdir)/mkspec.am

FREEBSD_VERS = 7.1
FREEBSD_RPMREL = 0.20090827.2
EXTRA_DIST += libs.add
EXTRA_DIST += target-libs.add
include ../libs.am

BINUTILS_VERS = 2.20
BINUTILS_PKGVERS = $(BINUTILS_VERS)
BINUTILS_RPMREL = 0.20091021.1
include ../binutils.am
BINUTILS_OPTS +=

GCC_VERS = 4.4.2
GCC_PKGVERS = $(GCC_VERS)
GCC_RPMREL = 0.20091021.1
include ../gcc.am
GCC_OPTS += --languages=cxx,fortran,objc
