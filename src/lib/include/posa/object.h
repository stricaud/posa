#ifndef _POS_OBJECT_H_
#define _POS_OBJECT_H_

#include <stdio.h>
#include <stdint.h>


enum _posa_object_constraint_t {
  P_CONSTRAINT_UNKNOWN,
  P_CONSTRAINT_REQUIRED,
  P_CONSTRAINT_OPTIONAL,
  P_CONSTRAINT_LIST,
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

struct _posa_object_enum_t {
  char *name;
  unsigned int value;
};
typedef struct _posa_object_enum_t posa_object_enum_t;

struct _posa_object_t {
  char *parent_name;
  char *name;

  int read_bits; // Number of bits read from data to build this object
  
  posa_object_constraint_t constraint;
  posa_object_type_t type;
  posa_object_type_t subtype;		/* Used for enum */

  posa_object_enum_t _enum[128];  
  int _enum_index;

  char p_char;
  int8_t p_int8;
  uint8_t p_uint8;
  int16_t p_int16;
  uint16_t p_uint16;
  int32_t p_int32;
  uint32_t p_uint32;
  int64_t p_int64;
  uint64_t p_uint64;

  char *string;
  size_t string_len;
};
typedef struct _posa_object_t posa_object_t;

posa_object_t *posa_object_new(char *name);
void posa_object_reset(posa_object_t *object);
posa_object_t *posa_object_copy(posa_object_t *origin);
void posa_object_enum_free(posa_object_t *object);
void posa_object_enum_append(posa_object_t *object, char *enum_name, unsigned int value);
void posa_object_free(posa_object_t *object);
void posa_object_debug(posa_object_t *object);

#endif // _POS_OBJECT_H_

