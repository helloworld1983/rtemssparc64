/*
 * Classic API Init task create failure
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.4 2009/09/04 21:28:56 joel Exp $
 */

/*
 *  Way too much stack space.  Should generate a fatal error
 *  on the init task create.
 */
#define CONFIGURE_HAS_OWN_INIT_TASK_TABLE
#define CONFIGURE_INIT_TASK_STACK_SIZE   RTEMS_MINIMUM_STACK_SIZE
rtems_initialization_tasks_table Initialization_tasks[] = {
  { rtems_build_name('I', 'N', 'I', ' '),
    RTEMS_MINIMUM_STACK_SIZE,
    1,
    RTEMS_DEFAULT_ATTRIBUTES,
    Init,
    RTEMS_DEFAULT_MODES,
    0
  }
};
#define CONFIGURE_INIT_TASK_TABLE Initialization_tasks
#define CONFIGURE_INIT_TASK_TABLE_SIZE \
  sizeof(CONFIGURE_INIT_TASK_TABLE) / sizeof(rtems_initialization_tasks_table)

#define FATAL_ERROR_TEST_NAME            "9"
#define FATAL_ERROR_DESCRIPTION          "Core invalid workspace address"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_CORE 
#define FATAL_ERROR_EXPECTED_IS_INTERNAL TRUE
#define FATAL_ERROR_EXPECTED_ERROR       INTERNAL_ERROR_INVALID_WORKSPACE_ADDRESS

void force_error()
{
  Configuration.work_space_start = NULL;

  rtems_initialize_data_structures();
  /* we will not run this far */
}
