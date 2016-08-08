#include <stdio.h>
#include <string.h>

#include <posa/posa.h>
#include <posa/object.h>
#include <posa/pos-table.h>
#include <posa/pos-errors.h>
#include <posa/pos-table-read.h>
#include <posa/utils.h>

int posa_foreach_object_main(posa_t *posa, pos_table_t *pos_table, object_children_cb_t pos_main_children, char *buffer, posa_object_t *object, void *user_data)
{
  return posa_foreach_object(posa, pos_table, NULL, pos_main_children, buffer, object, user_data);
}

int posa_foreach_object(posa_t *posa, pos_table_t *pos_table, char *object_name, object_children_cb_t pos_main_children, char *buffer, posa_object_t *object, void *user_data)
{
  int i;
  int start_main = 0;
  int processed_size = 0;
  
  for (i=0; i < pos_table->len; i++) {
    pos_instructions_t *pi = pos_table->pi[i];
    if (pi->nbspaces == 0) {
      if (start_main) {
	return 0; // We are done.
      }      
      if (!strcmp(pi->token1,object_name?"Object":"Object<main>")) {
	if (!object_name) {
	  start_main = 1;
	  continue;
	} else {
	  if (!strcmp(pi->token2, object_name)) {
	    start_main = 1;
	    continue;
	  }
	}
      }
    }
    
    if (start_main) {
      processed_size = pos_main_children(posa, pi->token1, pi->token2, pi, buffer, object, user_data);
      //      printf("size read:%d\n", processed_size);
      *buffer += processed_size;
    }
  }

  if (!start_main) return POS_ERR_NO_OBJECT_MAIN;

  return 0;
}
