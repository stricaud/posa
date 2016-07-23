#ifndef _POS_TABLE_H_
#define _POS_TABLE_H_

#include "pos-instructions.h"

struct _pos_table_t {
  int len;
  int nblines; // The initial state of the number of lines contained by the buffer
  pos_instructions_t **pi;
};
typedef struct _pos_table_t pos_table_t;

pos_table_t *pos_table_new(int nblines);
void pos_table_free(pos_table_t *pos_table);
int pos_table_append(pos_table_t *pos_tabe, pos_instructions_t *pi);
void pos_table_debug(pos_table_t *pos_table);


#endif // _POS_TABLE_H_
