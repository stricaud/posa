#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <posa/object.h>
#include <posa/pos-parser.h>
#include <posa/pos-table.h>
#include <posa/pos-instructions.h>
#include <posa/utils.h>

posa_object_t *posa_object_new(char *name)
{
  posa_object_t *object;

  object = malloc(sizeof(posa_object_t));
  if (!object) {
    fprintf(stderr, "Error allocating posa_object_t!\n");
    return NULL;
  }

  posa_object_reset(object);
  
  return object;
}

void posa_object_reset(posa_object_t *object)
{
  object->parent_name = NULL;
  object->name = NULL;
  
  object->constraint = P_CONSTRAINT_UNKNOWN;
  object->type = P_TYPE_UNKNOWN;
  object->subtype = P_TYPE_UNKNOWN;
}

void posa_object_free(posa_object_t *object)
{

}

void posa_object_debug(posa_object_t *object)
{

  posa_utils_red_printf("%s\t", object->name);
  
  switch(object->constraint) {
  case P_CONSTRAINT_REQUIRED:
    posa_utils_yellow_printf("required ");
    break;
  case P_CONSTRAINT_OPTIONAL:
    posa_utils_yellow_printf("optional ");
    break;
  case P_CONSTRAINT_LIST:
    posa_utils_yellow_printf("list ");
    break;
  default:
    posa_utils_yellow_printf("unknown ");    
  }

  switch(object->type) {
  case P_TYPE_UNKNOWN:
    posa_utils_green_printf("unknown\n");
    break;
  case P_TYPE_UINT16:
    posa_utils_green_printf("uint16(%d)\n", (unsigned int)object->p_uint16);
    break;
  case P_TYPE_INT16:
    posa_utils_green_printf("int16(%d)\n", object->p_int16);
    break;
  case P_TYPE_UINT32:
    posa_utils_green_printf("uint32(%d)\n", (unsigned int)object->p_uint32);
    break;
  case P_TYPE_INT32:
    posa_utils_green_printf("int32(%d)\n", object->p_int32);
    break;
  case P_TYPE_ENUM:
    posa_utils_green_printf("enum int16(%d)\n", object->p_int16);
    break;
  default:
    printf("unknown unknown\n");    
  }

}

