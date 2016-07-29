#include <stdio.h>
#include <stdlib.h>

#include <posa/pack.h>

#define POSA_DEBUG 0

unsigned char *posa_pack_uint16(uint16_t i, uint16_t *outlen)
{
  unsigned char *buf;

  *outlen = 2;

  buf = malloc(*outlen);
  
  buf[0] = (i >> 8) & 0xFF;
  buf[1] = i & 0xFF;

#ifdef POSA_DEBUG
fprintf(stderr, "%s: input=%d; buf[0]=%X buf[1]=%X\n", __FUNCTION__, i, (unsigned char)buf[0], (unsigned char)buf[1]);
#endif  
  
  return buf;
}
