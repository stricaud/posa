#ifndef _POS_TABLE_READ_H_
#define _POS_TABLE_READ_H_

#include <posa/posa.h>
#include <posa/pos-instructions.h>
#include <posa/object.h>

typedef void (*object_children_cb_t)(posa_t *posa, char *objectprop, char *objectname, pos_instructions_t *pi, char *buffer, posa_object_t *object, void *user_data);
int posa_foreach_object_main(posa_t *posa, pos_table_t *pos_table, object_children_cb_t pos_main_children, char *buffer, posa_object_t *object, void *user_data);
int posa_foreach_object(posa_t *posa, pos_table_t *pos_table, char *object_name, object_children_cb_t pos_main_children, char *buffer, posa_object_t *object, void *user_data);

#endif // _POS_TABLE_READ_H_
