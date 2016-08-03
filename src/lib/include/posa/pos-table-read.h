#ifndef _POS_TABLE_READ_H_
#define _POS_TABLE_READ_H_

#include "pos-instructions.h"

typedef void (*object_children_cb_t)(char *objectprop, char *objectname, pos_instructions_t *pi, char *buffer, void *user_data);
int posa_foreach_object_main(pos_table_t *pos_table, object_children_cb_t pos_main_children, char *buffer, void *user_data);
int posa_foreach_object(pos_table_t *pos_table, char *object_name, object_children_cb_t pos_main_children, char *buffer, void *user_data);

#endif // _POS_TABLE_READ_H_
