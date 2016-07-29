#include <posa/unpack.h>

uint16_t posa_unpack_uint16(unsigned char *buf)
{
  uint8_t b0, b1;

  b0 = buf[0];
  b1 = buf[1];

  return (b0 << 8) | b1;
}

