#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <posa/loop.h>
#include <posa/object.h>
#include <posa/utils.h>
#include <posa/pos-parser.h>
#include <posa/pos-table-read.h>
#include <posa/unpack.h>

#define PRINT_DEBUG 1

static int _handle_enum(posa_t *posa, pos_instructions_t *pi, posa_object_t *object)
{

  if ((!strcmp(pi->token1, "required")) || (!strcmp(pi->token1, "optional")) || (!strcmp(pi->token1, "list"))) {
    
  }
  
  return 0;
}

static int _object_set_constraint(posa_object_t *object, pos_instructions_t *pi)
{
  int retval = 0;
  
  if (!strcmp(pi->token1, "required")) {
    object->constraint = P_CONSTRAINT_REQUIRED;
    retval = 1;
  } else if (!strcmp(pi->token1, "optional")) {
    object->constraint = P_CONSTRAINT_OPTIONAL;
    retval = 1;
  } else if (!strcmp(pi->token1, "list")) {
    object->constraint = P_CONSTRAINT_LIST;
    retval = 1;
  }

  return retval;
}

static int _object_set_type(posa_object_t *object, pos_instructions_t *pi)
{
  int retval = 1;
  
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
  } else if (!strcmp(pi->token2, "string")) {
    object->type = P_TYPE_STRING;
  } else {
    retval = 0;
  }

  return retval;
}

static int _object_type_object(pos_instructions_t *pi)
{
  if (!strcmp(pi->token2, "object")) {
    return 1;
  }

  return 0;
}

static int _object_set_value(posa_object_t *object, char *buffer)
{
  int retval = 1;
  
  switch(object->type) {
  case P_TYPE_UINT16:
    object->p_uint16 = posa_unpack_uint16(buffer);
    object->read_bits = 16;
    break;
  case P_TYPE_INT16:
    object->p_int16 = posa_unpack_int16(buffer);
    object->read_bits = 16;
    break;
  case P_TYPE_UINT32:
    object->p_uint32 = posa_unpack_uint32(buffer);
    object->read_bits = 32;
    break;
  case P_TYPE_INT32:
    object->p_int32 = posa_unpack_int32(buffer);    
    object->read_bits = 32;
    break;
  case P_TYPE_ENUM:
    object->p_uint16 = posa_unpack_uint16(buffer);
    object->read_bits = 16;
    break;
  case P_TYPE_STRING:
    break;
  case P_TYPE_STRINGLEN:
    break;
  default:
    retval = 0;
  }

  return retval;
}

static void _object_set_name(posa_object_t *object, pos_instructions_t *pi)
{
  object->name = pi->token3;
}

/* static int _object_inside(posa_t *posa, char *objectprops, char *objectname, pos_instructions_t *pi, char *buffer, posa_object_t *object, void *user_data) */
/* { */
/*   printf("%s\n", pi->token3); */
/* } */

static void _object_exec_callback(posa_handler_cb_t callback, posa_t *posa, posa_object_t *object, char *buffer, size_t buffer_size, void *user_data)
{
  callback(posa, object, buffer, buffer_size, user_data);
  printf("wholebuf:%X\n", buffer);
  printf("read=%d;buf=%X\n", object->read_bits / 8, buffer[0]);
  *buffer += object->read_bits / 8;
  printf("newbuf=%X\n", buffer[0]);
  
}

static int _object_main(posa_t *posa, char *objectprops, char *objectname, pos_instructions_t *pi, char *buffer, posa_object_t *object, void *user_data)
{
  posa_handler_cb_t callback = (posa_handler_cb_t)user_data;

  int has_constraint;
  int has_type;  
  int do_reset = 0;

  posa->lines_read++;
  
  has_constraint = _object_set_constraint(object, pi);
  has_type = _object_set_type(object, pi);
  _object_set_value(object, buffer);
  _object_set_name(object, pi);

  if (!has_type) {
    if (_object_type_object(pi)) {
      posa_foreach_object(posa, posa->table, pi->token3, _object_main, buffer, object, user_data);
    }
  }
  
  /* printf("token3:%s accumulator:%d\n", pi->token3, posa->obj_accumulator?1:0); */
  if (posa->obj_accumulator) {
    if (has_constraint) { // or line == line_end {
      _object_exec_callback(callback, posa, posa->obj_accumulator, buffer, 0, user_data);
      posa->obj_accumulator = NULL;
    }
  }
  
  //  printf("has type=%d\n", has_type);
  if (has_constraint) {
    if (object->type == P_TYPE_ENUM) {
      posa->obj_accumulator = posa_object_copy(object);
      return 0;
    } else {
      //	printf("obj name:%s\n", object->name);
      _object_exec_callback(callback, posa, object, buffer, 0, user_data);
    }
    do_reset = 1;
  } else {
    uint16_t value = (uint16_t)strtol(pi->token3, NULL, 16);
    posa_object_enum_append(posa->obj_accumulator, pi->token1, value);    
  }
  
  if (do_reset) {
    posa_object_reset(object);
  }
  
  return 0;
}


int posa_loop_from_file(posa_t *posa, char *filename, size_t readsize, posa_handler_cb_t callback, void *user_data)
{
  posa_object_t *object;
  int nblines;
  int i;

  object = posa_object_new(NULL);

  posa->binbuf = posa_utils_make_buffer_from_file(filename, &posa->binbuf_size);

  nblines = posa_parser_count_lines((char *)posa->desc, posa->desc_size);
  posa->table = posa_parser_handle_buffer((char *)posa->desc, posa->desc_size, nblines);

#ifdef PRINT_DEBUG
  for (i=0; i < posa->binbuf_size; i++) {
    printf("%X", posa->binbuf[i]);
  }
  printf("\n");
#endif  

  posa_foreach_object_main(posa, posa->table, _object_main, posa->binbuf, object, callback);

/* typedef void (*posa_handler_cb_t)(posa_t *posa, posa_object_t *object, const unsigned char *buffer, size_t buffer_size, void *user_data); */

//  callback(posa, 
  
  return 0;
}

