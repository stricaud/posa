#ifndef _POS_INSTRUCTIONS_H_
#define _POS_INSTRUCTIONS_H_

#include <posa/object.h>


struct _pos_instructions_t {
  int line_in_file;
  int nbspaces;
  char *token1;
  char *token2;
  char *token3;
  char *token4;
  char *token5;
  char *token6;
  char *token7;

  pos_object_t object;
};
typedef struct _pos_instructions_t pos_instructions_t;

void pi_debug(pos_instructions_t *pi);
void pi_free(pos_instructions_t *pi);

#endif // _POS_INSTRUCTIONS_H_
