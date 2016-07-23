#ifndef _POS_OBJECT_H_
#define _POS_OBJECT_H_

#include <stdint.h>

enum _pos_type_t {
  POS_TYPE_UNKNOWN,
  POS_TYPE_BYTE,
  POS_TYPE_BIT,
  POS_TYPE_INT8,
  POS_TYPE_UINT8,
  POS_TYPE_INT16,
  POS_TYPE_UINT16,
  POS_TYPE_INT32,
  POS_TYPE_UINT32,
  POS_TYPE_INT64,
  POS_TYPE_UINT64,
  POS_TYPE_INT128,
  POS_TYPE_UINT128,
  POS_TYPE_STRING,
  POS_TYPE_STRINGLEN,
};
typedef enum _pos_type_t pos_type_t;

struct _pos_object_t {
  pos_type_t type;
  size_t     type_len; // Sometimes the type requires a len

  char pos_char;
  int8_t pos_int8;
  uint8_t pos_uint8;
  int16_t pos_int16;
  uint16_t pos_uint16;
  int32_t pos_int32;
  uint32_t pos_uint32;
  int64_t pos_int64;
  uint64_t pos_uint64;

  char *string;
  size_t string_len;
  
};
typedef struct _pos_object_t pos_object_t;


#endif // _POS_OBJECT_H_

