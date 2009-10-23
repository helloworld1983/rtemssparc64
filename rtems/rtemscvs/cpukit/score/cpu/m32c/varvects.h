/*

Copyright (c) 2008 Red Hat Incorporated.
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met: 

    Redistributions of source code must retain the above copyright 
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    The name of Red Hat Incorporated may not be used to endorse 
    or promote products derived from this software without specific 
    prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL RED HAT INCORPORATED BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

*/

/* This file defines the interface to the built-in variable vector
   table in R8C/M16C/M32C chips.  */

#ifndef _VARVECTS_H_
#define _VARVECTS_H_

typedef void (*_m32c_interrupt_func)(void) __attribute__((mode(SI)));
extern _m32c_interrupt_func _var_vects[];

#if defined(__r8c_cpu__) || defined (__m16c_cpu__)

#define _set_var_vect(f,n) \
  { asm ("mov.w #%%lo16(%d0),__var_vects+%d1" : : "s" (f), "g" (n*4));	\
    asm ("mov.w #%%hi16(%d0),__var_vects+%d1" : : "s" (f), "g" (n*4+2)); }

#else

#define _set_var_vect(f,n) \
  _var_vects[n] = f

#endif
#endif
