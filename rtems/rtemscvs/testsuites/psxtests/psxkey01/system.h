/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: system.h,v 1.1 2008/02/04 19:39:43 jennifer Exp $
 */

/* functions */

#include <pmacros.h>

void *POSIX_Init(
  void *argument
);

void *Task_1(
  void *argument
);


/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS  21
#define CONFIGURE_MAXIMUM_POSIX_KEYS     21

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#include <rtems/confdefs.h>

/* global variables */

#ifdef CONFIGURE_INIT
#define TEST_EXTERN
#else
#define TEST_EXTERN extern
#endif

TEST_EXTERN pthread_t        Init_id;
TEST_EXTERN pthread_t        Task_id[CONFIGURE_MAXIMUM_POSIX_THREADS-1];
TEST_EXTERN pthread_key_t    Key_id[CONFIGURE_MAXIMUM_POSIX_KEYS-1];
TEST_EXTERN uint32_t   Data_array[ CONFIGURE_MAXIMUM_POSIX_THREADS ];

#undef TEST_EXTERN
/* end of include file */
