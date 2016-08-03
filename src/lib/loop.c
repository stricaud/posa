#include <posa/loop.h>
#include <posa/object.h>
#include <posa/utils.h>
#include <posa/pos-parser.h>
#include <posa/pos-table-read.h>

void object_children(pos_instructions_t *pi, char *buffer, void *user_data)
{

  pi_debug(pi);
  /* uint16_t u16; */
  
  /* if (!strcmp(pi->token2, "uint16")) { */
  /*   posa_utils_red_printf("%s: ", pi->token3); */
  /*   u16 = posa_unpack_uint16(buffer); */
  /*   posa_utils_blue_printf("%d\n", u16); */
  /* } */

}



// cnt = number of wanted objects, 0 shoud be defaults
int posa_loop_from_file(posa_t *posa, char *filename, size_t readsize, posa_handler_cb_t callback, void *user_data)
{
  posa_object_t *object;
  int nblines;

  posa->binbuf = posa_utils_make_buffer_from_file(filename, &posa->binbuf_size);

  nblines = posa_parser_count_lines((char *)posa->desc, posa->desc_size);
  posa->table = posa_parser_handle_buffer((char *)posa->desc, posa->desc_size, nblines);

  posa_foreach_object_main(posa->table, object_children, posa->binbuf, NULL);

/* typedef void (*posa_handler_cb_t)(posa_t *posa, posa_object_t *object, const unsigned char *buffer, size_t buffer_size, void *user_data); */

//  callback(posa, 

  
  return 0;
}

