/*
 * Copyright (c) 2009 by
 * Ralf Corsépius, Ulm, Germany. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include <unistd.h>

int
main (void)
{
  int filedes[2];
  int status;

  status = pipe (filedes);

  return 0;
}
