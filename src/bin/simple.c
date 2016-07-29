#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <posa/posa.h>
#include <posa/pack.h>
#include <posa/unpack.h>

int main(int argc, char **argv)
{
  posa_t *posa;
  uint16_t i;
  uint16_t outlen;
  char *buf;
  
  posa = posa_init(&argc, &argv);
  buf = malloc(24);
  
  buf = posa_pack_uint16(42, &outlen);

  printf("buf[0]=%X buf[1]=%X outlen=%d\n", (unsigned char)buf[0], (unsigned char)buf[1], outlen);
  i = posa_unpack_uint16(buf);

  printf("unpacked value:%d\n", i);
  
  free(buf);
  posa_free(posa);
  
  return 0;
}
