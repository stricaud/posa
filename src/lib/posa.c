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

  return posa;
}

void posa_free(posa_t *posa)
{
  free(posa);
}
