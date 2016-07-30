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

char *buf;

void object_children(pos_instructions_t *pi, char *buffer, void *user_data)
{
  uint16_t u16;
  
  if (!strcmp(pi->token2, "uint16")) {
    posa_utils_red_printf("%s: ", pi->token3);
    u16 = posa_unpack_uint16(buffer);
    posa_utils_blue_printf("%d\n", u16);
  }

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
  buf = malloc(POSA_MAX_BUFSIZE);
  if (!buf) {
    fprintf(stderr, "Cannot allocate the buffer!\n");
    return -1;
  }

  posa_desc = posa_utils_make_buffer_from_file(argv[1], &posa_desc_size);
  binbuf = posa_utils_make_buffer_from_file(argv[2], &binbuf_size);

  nblines = count_lines((char *)posa_desc, posa_desc_size);
  pos_table = handle_buffer((char *)posa_desc, posa_desc_size, nblines);
  
  /* printf("Starting foreach object main\n"); */
  posa_foreach_object_main(pos_table, object_children, binbuf, NULL);

  /* buf = posa_pack_uint16(42, &outlen); */
  /* printf("buf[0]=%X buf[1]=%X outlen=%d\n", (unsigned char)buf[0], (unsigned char)buf[1], outlen); */
  /* i = posa_unpack_uint16(buf); */

  /* printf("unpacked value:%d\n", i); */
  pos_table_free(pos_table);
  free(buf);
  free(binbuf);
  posa_free(posa);
  
  return 0;
}
