#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <arpa/inet.h>

#include <posa/pos-parser.h>
#include <posa/pos-instructions.h>
#include <posa/pos-table.h>
#include <posa/pos-table-read.h>
#include <posa/utils.h>

void object_children(pos_instructions_t *pi, char *buffer, void *user_data)
{
  //  pi_debug(pi);
  uint16_t id;

  /* printf("%x:%x:%x:%x---", buffer[0], buffer[1], buffer[2], buffer[3]); */
  
  /* if (!strcmp(pi->token2, "int16")) { */
  /*   memcpy(&id, buffer, 1); */
  /*      *buffer += sizeof(uint16_t); */
  /*   printf("id:%d\n", id); */
  /* } */
  if (!strcmp(pi->token2, "uint16")) {
    memcpy(&id, buffer, 1);
       *buffer += sizeof(uint16_t);
    printf("id:%d\n", ntohs(id));
  }
  /* if (!strcmp(pi->token2, "enum<int16>")) { */
  /*   memcpy(&id, buffer, 1); */
  /*      *buffer += sizeof(int16_t); */
  /*   printf("id:%d\n", id); */
  /* } */

}


int main(int argc, char **argv)
{
  char *buffer;
  char *binbuf;
  size_t buffer_size;
  int nblines;
  pos_table_t *pos_table;
  int i;

  if (argc < 3) {
    fprintf(stderr, "%s file.pos file.bin\n", argv[0]);
    return -1;
  }

  buffer = posa_utils_make_buffer_from_file(argv[1], &buffer_size);

  printf("buffer size:%ld\n", buffer_size);
  
  nblines = posa_parser_count_lines((char *)buffer, buffer_size);
  pos_table = posa_parser_handle_buffer((char *)buffer, buffer_size, nblines);

  pos_table_debug(pos_table);

  /* bin_fp = fopen(argv[2], "rb"); */
  binbuf = posa_utils_make_buffer_from_file(argv[2], &buffer_size);
  
  printf("Starting foreach object main\n");
  posa_foreach_object_main(pos_table, object_children, binbuf, NULL);
  /* printf("Starting foreach object Queries\n"); */
  /* posa_foreach_object(pos_table, "Queries", object_children, binbuf, NULL); */

  
  /* fclose(bin_fp); */
  
  pos_table_free(pos_table);

  free(buffer);
  free(binbuf);
  posa_utils_red_printf("Finished\n");
  posa_utils_blue_printf("Finished\n");
  posa_utils_green_printf("Finished\n");
  posa_utils_yellow_printf("Finished\n");
  
  return 0;
}
