#include <posa/unpack.h>

int32_t posa_unpack_int32(unsigned char *buf)
{
  int8_t b0, b1, b2, b3;

  b0 = buf[0];
  b1 = buf[1];
  b2 = buf[2];
  b3 = buf[3];

  return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

uint32_t posa_unpack_uint32(unsigned char *buf)
{
  return (uint32_t)posa_unpack_int32(buf);
}

int16_t posa_unpack_int16(unsigned char *buf)
{
  int8_t b0, b1;

  b0 = buf[0];
  b1 = buf[1];

  return (b0 << 8) | b1;
}

uint16_t posa_unpack_uint16(unsigned char *buf)
{
  return (uint16_t)posa_unpack_int16(buf);
}
