#include <stdio.h>

#include <posa/posa.h>

int main(int argc, char **argv)
{
  posa_t *posa;
  
  posa = posa_init(&argc, &argv);

  posa_free(posa);
  
  return 0;
}
