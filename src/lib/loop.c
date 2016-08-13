#include <stdio.h>
#include <string.h>

#include <posa/loop.h>
#include <posa/object.h>
#include <posa/utils.h>
#include <posa/pos-parser.h>
#include <posa/pos-table-read.h>
#include <posa/unpack.h>

static int _handle_enum(posa_t *posa, pos_instructions_t *pi, posa_object_t *object)
{

  if ((!strcmp(pi->token1, "required")) || (!strcmp(pi->token1, "optional")) || (!strcmp(pi->token1, "list"))) {
    
  }
  
  return 0;
}

static void _object_set_constraint(posa_object_t *object, pos_instructions_t *pi)
{  
  if (!strcmp(pi->token1, "required")) {
    object->constraint = P_CONSTRAINT_REQUIRED;
  } else if (!strcmp(pi->token1, "optional")) {
    object->constraint = P_CONSTRAINT_OPTIONAL;
  } else if (!strcmp(pi->token1, "list")) {
    object->constraint = P_CONSTRAINT_LIST;
  } 
}

static void _object_set_type(posa_object_t *object, pos_instructions_t *pi)
{
  
  if (!strcmp(pi->token2, "uint16")) {
    object->type = P_TYPE_UINT16;
    /* processed_size = 2; */
    /* buffer += 2; */
  } else if (!strcmp(pi->token2, "int16")) {
    object->type = P_TYPE_INT16;
    /* processed_size = 2; */
  } else if (!strcmp(pi->token2, "uint32")) {
    object->type = P_TYPE_UINT32;
    /* processed_size = 4; */
  } else if (!strcmp(pi->token2, "int32")) {
    object->type = P_TYPE_INT32;
    /* processed_size = 4; */
  } else if (!strcmp(pi->token2, "enum<int16>")) {
    object->type = P_TYPE_ENUM;
    object->subtype = P_TYPE_INT16;
    /* processed_size = 2; */
    /* posa->obj_accumulator = posa_object_copy(object); */
  }
}

static void _object_set_value(posa_object_t *object, char *buffer)
{
  switch(object->type) {
  case P_TYPE_UINT16:
    object->p_uint16 = posa_unpack_uint16(buffer);
    break;
  case P_TYPE_INT16:
    object->p_int16 = posa_unpack_int16(buffer);
    break;
  case P_TYPE_UINT32:
    object->p_uint32 = posa_unpack_uint32(buffer);
    break;
  case P_TYPE_INT32:
    object->p_int32 = posa_unpack_int32(buffer);    
    break;
  case P_TYPE_ENUM:
    object->p_uint16 = posa_unpack_int16(buffer);
    break;    
  }
}

static void _object_set_name(posa_object_t *object, pos_instructions_t *pi)
{
  object->name = pi->token3;
}

static int _object_main(posa_t *posa, char *objectprops, char *objectname, pos_instructions_t *pi, char *buffer, posa_object_t *object, void *user_data)
{
  posa_handler_cb_t callback = (posa_handler_cb_t)user_data;

  _object_set_constraint(object, pi);
  _object_set_type(object, pi);
  _object_set_value(object, buffer);
  _object_set_name(object, pi);  
  
  callback(posa, object, buffer, 0, user_data);
  
  posa_object_reset(object);
  
  return 0;
}


#if 0
static int _object_main(posa_t *posa, char *objectprops, char *objectname, pos_instructions_t *pi, char *buffer, posa_object_t *object, void *user_data)
{
  /* posa_object_t *object = (posa_object_t *)user_data; */
  posa_handler_cb_t callback = (posa_handler_cb_t)user_data;

  static int processed_size = 0;
  
  object->parent_name = objectname;

  if (posa->obj_accumulator) {
    // We accumulate, we are in an enumeration
    if ((!strcmp(pi->token1, "required")) || (!strcmp(pi->token1, "optional")) || (!strcmp(pi->token1, "list"))) {
      //posa_object_free(object);
      object = posa_object_copy(posa->obj_accumulator);
      posa_object_free(posa->obj_accumulator);

      callback(posa, object, buffer, 0, user_data);
    } else {
      uint16_t value = (uint16_t)strtol(pi->token3, NULL, 16);
      posa_object_enum_append(object, pi->token1, value);
      //      printf("key=%s, value=%d\n", pi->token1, value);
    }
  } else {
  // token 1
  if (!strcmp(pi->token1, "required")) {
    object->constraint = P_CONSTRAINT_REQUIRED;
  } else if (!strcmp(pi->token1, "optional")) {
    object->constraint = P_CONSTRAINT_OPTIONAL;
  } else if (!strcmp(pi->token1, "list")) {
    object->constraint = P_CONSTRAINT_LIST;
  } else {
    // We may be reading elements of an enum
  }

  // token 2
  if (!strcmp(pi->token2, "uint16")) {
    object->type = P_TYPE_UINT16;
    object->p_uint16 = posa_unpack_uint16(buffer);
    processed_size = 2;
    buffer += 2;
  } else if (!strcmp(pi->token2, "int16")) {
    object->type = P_TYPE_INT16;
    object->p_int16 = posa_unpack_int16(buffer);
    processed_size = 2;
  } else if (!strcmp(pi->token2, "uint32")) {
    object->type = P_TYPE_UINT32;
    object->p_uint32 = posa_unpack_uint32(buffer);
    processed_size = 4;
  } else if (!strcmp(pi->token2, "int32")) {
    object->type = P_TYPE_INT32;
    object->p_int32 = posa_unpack_int32(buffer);
    processed_size = 4;
  } else if (!strcmp(pi->token2, "enum<int16>")) {
    object->type = P_TYPE_ENUM;
    object->subtype = P_TYPE_INT16;
    object->p_uint16 = posa_unpack_int16(buffer);
    processed_size = 2;

    posa->obj_accumulator = posa_object_copy(object);
  }  

  object->name = pi->token3;

  if (!posa->obj_accumulator) {
    callback(posa, object, buffer, 0, user_data);
  }

  posa_object_reset(object);
  }
  
  return processed_size;
}
#endif

int posa_loop_from_file(posa_t *posa, char *filename, size_t readsize, posa_handler_cb_t callback, void *user_data)
{
  posa_object_t *object;
  int nblines;
  int i;

  object = posa_object_new(NULL);

  posa->binbuf = posa_utils_make_buffer_from_file(filename, &posa->binbuf_size);

  nblines = posa_parser_count_lines((char *)posa->desc, posa->desc_size);
  posa->table = posa_parser_handle_buffer((char *)posa->desc, posa->desc_size, nblines);

  for (i=0; i < posa->binbuf_size; i++) {
    printf("%X", posa->binbuf[i]);
  }
  printf("\n");

  posa_foreach_object_main(posa, posa->table, _object_main, posa->binbuf, object, callback);

/* typedef void (*posa_handler_cb_t)(posa_t *posa, posa_object_t *object, const unsigned char *buffer, size_t buffer_size, void *user_data); */

//  callback(posa, 

  
  return 0;
}

