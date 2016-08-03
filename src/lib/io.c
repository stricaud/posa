#include <stdio.h>
#include <stdlib.h>

#include <posa/io.h>
#include <posa/pos-parser.h>
#include <posa/utils.h>

int posa_io_open(posa_t *posa, char *posa_desc_filepath)
{
  posa->desc = posa_utils_make_buffer_from_file(posa_desc_filepath, &posa->desc_size);
  if(!posa->desc) {
    fprintf(stderr, "Cannot open description file %s\n", posa_desc_filepath);
    return -1;
  }    
  return 0;
}

int posa_io_close(posa_t *posa)
{
  pos_table_free(posa->table);
  /* free(posa->binbuf); */
  return 0;
}
