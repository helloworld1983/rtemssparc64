/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: isatty_r.c,v 1.3 2009/09/30 08:20:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

/*
 *  _isatty_r
 *
 *  This is the Newlib dependent reentrant version of isatty().
 */

#if defined(RTEMS_NEWLIB) && !defined(HAVE__ISATTY_R)

#include <reent.h>
#include <sys/stat.h>

int _isatty_r(
  struct _reent *ptr __attribute__((unused)),
  int            fd
)
{
  return isatty( fd );
}
#endif
