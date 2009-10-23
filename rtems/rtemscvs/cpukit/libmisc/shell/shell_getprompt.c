/*
 *  Dynamically build the shell prompt 
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: shell_getprompt.c,v 1.1 2008/08/27 12:48:41 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <time.h>

#include <rtems.h>
#include <rtems/error.h>
#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/system.h>
#include <rtems/shell.h>
#include "internal.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

void rtems_shell_get_prompt(
  rtems_shell_env_t *shell_env,
  char              *prompt,
  size_t             size
)
{
  char curdir[256];
  
  /* XXX: show_prompt user adjustable */
  getcwd(curdir,sizeof(curdir));
  snprintf(prompt, size - 1, "%s%s[%s] %c ",
          ((shell_env->taskname) ? shell_env->taskname : ""),
          ((shell_env->taskname) ? " " : ""),
          curdir,
          geteuid()?'$':'#');
}
