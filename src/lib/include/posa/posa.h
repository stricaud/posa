#ifndef _POSA_H_
#define _POSA_H_

#include <posa/pos-table.h>
#include <posa/object.h>

#define POSA_MAX_BUFSIZE 2048 // Will work for everything except strings, which in should be checked and have the buffer reallocated accordingly

#define POSA_API_VERSION 1

struct _posa_t {
  /* private */
  int lines_read;
  pos_table_t *table;
  char *desc;
  size_t desc_size;
  char *binbuf;
  size_t binbuf_size;  
  
  posa_object_t *obj_accumulator; // In the case of an enum, descriptions come after. They are appended to the previous object. This object will accumulate the options.

  /* public */
  int little_endian;
  
};
typedef struct _posa_t posa_t;


posa_t *posa_init(int *argc, char ***agv);
void posa_free(posa_t *posa);

#endif // _POSA_H_
