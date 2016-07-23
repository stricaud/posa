#include <stdio.h>
#include <string.h>

#include <posa/pos-table.h>
#include <posa/pos-errors.h>
#include <posa/pos-table-read.h>
#include <posa/utils.h>

int posa_foreach_object_main(pos_table_t *pos_table, object_children_cb_t pos_main_children, char *buffer, void *user_data)
{
  return posa_foreach_object(pos_table, NULL, pos_main_children, buffer, user_data);
}

int posa_foreach_object(pos_table_t *pos_table, char *object_name, object_children_cb_t pos_main_children, char *buffer, void *user_data)
{
  int i;
  int start_main = 0;
  
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
      pos_main_children(pi, buffer, user_data);
    }
  }

  if (!start_main) return POS_ERR_NO_OBJECT_MAIN;
  
}
