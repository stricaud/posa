#ifndef _PACK_H_
#define _PACK_H_

#include <stdint.h>

unsigned char *posa_pack_int32(int32_t i, size_t *outlen);
unsigned char *posa_pack_uint32(uint32_t i, size_t *outlen);
unsigned char *posa_pack_int16(int16_t i, size_t *outlen);
unsigned char *posa_pack_uint16(uint16_t i, size_t *outlen);

#endif // _PACK_H_

