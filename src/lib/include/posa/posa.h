#ifndef _POSA_H_
#define _POSA_H_

#include <posa/pos-table.h>

#define POSA_MAX_BUFSIZE 2048 // Will work for everything except strings, which in should be checked and have the buffer reallocated accordingly

#define POSA_API_VERSION 1

struct _posa_t {
  int little_endian;
  pos_table_t *table;
  char *desc;
  size_t desc_size;
  char *binbuf;
  size_t binbuf_size;
};
typedef struct _posa_t posa_t;


posa_t *posa_init(int *argc, char ***agv);
void posa_free(posa_t *posa);

#endif // _POSA_H_
