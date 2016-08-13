#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <posa/posa.h>
#include <posa/pack.h>
#include <posa/unpack.h>
#include <posa/pos-parser.h>
#include <posa/pos-instructions.h>
#include <posa/pos-table.h>
#include <posa/pos-table-read.h>
#include <posa/utils.h>
#include <posa/io.h>
#include <posa/loop.h>

void posa_handler(posa_t *posa, posa_object_t *object, const unsigned char *buffer, size_t buffer_size, void *user_data)
{
  posa_object_debug(object);
}
		  
int main(int argc, char **argv)
{
  posa_t *posa;
  int number;

  if (argc < 3) {
    fprintf(stderr, "%s file.pos file.bin\n", argv[0]);
    return -1;
  }

  posa = posa_init(&argc, &argv);
  posa_io_open(posa, argv[1]);

  posa_loop_from_file(posa, argv[2], 0, posa_handler, NULL);

  posa_io_close(posa);  
  posa_free(posa);

  printf("0x8100 in int:%d\n", (uint16_t)strtol("0x8100", NULL, 16));
  /* posa_utils_buffer_to_int("0x8100", 4, &number); */
  /* printf("number:%d\n", number); */
  
  return 0;
}
