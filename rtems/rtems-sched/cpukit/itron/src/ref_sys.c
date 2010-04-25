/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ref_sys.c,v 1.1 2007/04/17 20:32:13 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/sysmgmt.h>

/*
 *  ref_sys - Reference System Status
 */

ER ref_sys(
  T_RSYS *pk_rsys
)
{
  return E_OK;
}
