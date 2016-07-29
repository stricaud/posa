#ifndef _POSA_H_
#define _POSA_H_

struct _posa_t {
  int little_endian;
};
typedef struct _posa_t posa_t;

posa_t *posa_init();
void posa_free(posa_t *posa);

#endif // _POSA_H_
