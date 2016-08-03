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
  uint16_t i;
  uint16_t outlen;

  char *posa_desc;
  size_t posa_desc_size;

  char *binbuf;
  size_t binbuf_size;
  
  pos_table_t *pos_table;
  int nblines;

  if (argc < 3) {
    fprintf(stderr, "%s file.pos file.bin\n", argv[0]);
    return -1;
  }

  posa = posa_init(&argc, &argv);
  posa_io_open(posa, argv[1]);


  posa_loop_from_file(posa, argv[2], 0, posa_handler, NULL);

  posa_io_close(posa);  
  posa_free(posa);
  
  return 0;
}
