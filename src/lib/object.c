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

  object->parent_name = NULL;
  object->name = name;
  
  object->constraint = P_CONSTRAINT_UNKNOWN;
  object->type = P_TYPE_UNKNOWN;
  object->subtype = P_TYPE_UNKNOWN;
  
  return object;
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

  printf("type: ");
  switch(object->type) {
  case P_TYPE_UINT16:
    posa_utils_green_printf("uint16(%d)\n", (unsigned int)object->p_uint16);
    break;
  default:
    printf("unknown\n");    
  }

}

int pos_objects_list(pos_table_t *pt)
{
  int i;
#if 0

  for (i = 0; i <= pt->len; i++) {
    if (pt->pi[i]) {
      if (!strcasecmp(pt->pi[i]->token1, "object")) {
	printf("object:%s\n", pt->pi[i]->token2);
      }
      if (!strcasecmp(pt->pi[i]->token1, "object<main>")) {
	printf("object main:%s\n", pt->pi[i]->token2);
      }

    }
  }  
#endif
}

