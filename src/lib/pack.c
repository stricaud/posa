#include <stdio.h>
#include <stdlib.h>

#include <posa/pack.h>

#define POSA_DEBUG 0

unsigned char *posa_pack_int32(int32_t i, size_t *outlen)
{
  unsigned char *buf;

  *outlen = 4;

  buf = malloc(*outlen);
  
  buf[0] = (i >> 24) & 0xFF;
  buf[1] = (i >> 16) & 0xFF;
  buf[2] = (i >> 8) & 0xFF;
  buf[3] = i & 0xFF;

#ifdef POSA_DEBUG
fprintf(stderr, "%s: input=%d; buf[0]=%X buf[1]=%X buf[2]=%X buf[3]=%X\n", __FUNCTION__, i, (unsigned char)buf[0], (unsigned char)buf[1], (unsigned char)buf[2], (unsigned char)buf[3]);
#endif  
  
  return buf;
}

unsigned char *posa_pack_uint32(uint32_t i, size_t *outlen)
{
  return posa_pack_int32((int32_t)i, outlen);
}

unsigned char *posa_pack_int16(int16_t i, size_t *outlen)
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

unsigned char *posa_pack_uint16(uint16_t i, size_t *outlen)
{
  return posa_pack_int16((int16_t)i, outlen);
}
