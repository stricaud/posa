#include <stdio.h>
#include <stdlib.h>

#include <posa/posa.h>

posa_t *posa_init(int *argc, char ***argv)
{
  posa_t *posa;
  posa = malloc(sizeof(posa_t));
  if (!posa) {
    fprintf(stderr, "Cannot allocate a posa object!\n");
    return NULL;
  }
  posa->little_endian = 1;
  posa->table = NULL;
  posa->desc = NULL;
  posa->desc_size = 0;
  posa->binbuf = NULL;
  posa->binbuf_size = 0;

  posa->obj_accumulator = NULL;

  return posa;
}

void posa_free(posa_t *posa)
{
  free(posa);
}
