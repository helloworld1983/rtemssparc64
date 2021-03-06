/*
 *  16.1.1 Thread Creation Attributes, P1003.1c/Draft 10, p, 140
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pthreadattrgetstacksize.c,v 1.4 2003/09/04 18:54:25 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include <errno.h>

int pthread_attr_getstacksize(
  const pthread_attr_t  *attr,
  size_t                *stacksize
)
{
  if ( !attr || !attr->is_initialized || !stacksize )
    return EINVAL;

  *stacksize = attr->stacksize;
  return 0;
}
