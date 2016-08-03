#ifndef _POS_OBJECT_H_
#define _POS_OBJECT_H_

#include <stdio.h>
#include <stdint.h>


enum _posa_object_constraint_t {
  P_REQUIRED,
  P_OPTIONAL,
  P_LIST,
};
typedef enum _posa_object_constraint_t posa_object_constraint_t;

enum _posa_object_type_t {
  P_TYPE_UNKNOWN,
  P_TYPE_BYTE,
  P_TYPE_BIT,
  P_TYPE_INT8,
  P_TYPE_UINT8,
  P_TYPE_INT16,
  P_TYPE_UINT16,
  P_TYPE_INT32,
  P_TYPE_UINT32,
  P_TYPE_INT64,
  P_TYPE_UINT64,
  P_TYPE_INT128,
  P_TYPE_UINT128,
  P_TYPE_STRING,
  P_TYPE_STRINGLEN,
  P_TYPE_ENUM,
};
typedef enum _posa_object_type_t posa_object_type_t;

struct _posa_object_t {
  char *parent_name;
  char *name;
  
  posa_object_type_t type;
  posa_object_type_t subtype;		/* Used for enum */
  
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
typedef struct _posa_object_t posa_object_t;


#endif // _POS_OBJECT_H_

