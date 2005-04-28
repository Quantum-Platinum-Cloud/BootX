/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 *  mem.c - Standard memory functions.
 *
 *  Copyright (c) 1998-2002 Apple Computer, Inc.
 *
 *  DRI: Josh de Cesare
 */

#import <libclite.h>
#import <ci.h>


void *memcpy(void *dst, const void *src, size_t len)
{
  const char *s = src;
  char       *d = dst;
  int        pos = 0, dir = 1;

  if (d > s) {
    dir = -1;
    pos = len - 1;
  }

  while (len--) {
    d[pos] = s[pos];
    pos += dir;
  }

  return dst;
}


void *memset(void *dst, int ch, size_t len)
{
  long tmp = 0x01010101 * (ch & 0x000000FF);

  if (len < 32) while (len--) *(((char *)dst)++) = ch;
  else {
    // do the front chunk as chars
    while ((long)dst & 3) {
      len--;
      *(((char *)dst)++) = ch;
    }
    
    // do the middle chunk as longs
    while (len > 3) {
      len -= 4;
      *(((long *)dst)++) = tmp;
    }
    
    // do the last chunk as chars
    while (len--) *(((char *)dst)++) = ch;
  }

  return dst;
}


int
memcmp(const void *b1, const void *b2, size_t len)
{
  register long n = len;
  unsigned char *m1 = (unsigned char *)b1;
  unsigned char *m2 = (unsigned char *)b2;
  
  while (n-- && (*m1 == *m2)) {
    m1++;
    m2++;
  }
  
  return ((n < 0) ? 0 : (*m1 - *m2));
}


void bcopy(const void *src, void *dst, size_t len)
{
  memcpy(dst, src, len);
}

void bzero(void *dst, int len)
{
  memset(dst, 0, len);
}

