/** 
 *  @file  score/src/ts64toticks.c
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ts64toticks.c,v 1.2 2008/12/16 17:36:01 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/score/timestamp.h>
#include <rtems/score/tod.h>

#if defined(CPU_RTEMS_SCORE_TIMESTAMP_IS_INT64) && \
    !defined(CPU_RTEMS_SCORE_TIMESTAMP_INT64_INLINE)
uint32_t _Timestamp64_To_ticks(
  const Timestamp64_Control *time
)
{
  uint32_t ticks;

  ticks = *time / rtems_configuration_get_nanoseconds_per_tick();
  if ( ticks )
    return ticks;
  return 1;
}
#endif
