#ifndef _UNPACK_H_
#define _UNPACK_H_

#include <stdint.h>

int32_t posa_unpack_int32(unsigned char *buf);
uint32_t posa_unpack_uint32(unsigned char *buf);
int16_t posa_unpack_int16(unsigned char *buf);
uint16_t posa_unpack_uint16(unsigned char *buf);

#endif // _UNPACK_H_
