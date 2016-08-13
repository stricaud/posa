#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

void _posa_utils_color_printf(char *colorseq, char *fmt, ...)
{
  va_list ap;
  
  /* printf("\033[1;31m%s\033[0m", fmt); */
  va_start(ap, fmt);
  fprintf(stderr, "%s", colorseq);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\033[0m");
  va_end(ap);
}

char *posa_utils_make_buffer_from_file(char *filepath, size_t *buffer_size)
{
  FILE *fp;
  long offset;
  char *buffer;
  size_t read_size;

  fp = fopen(filepath, "rb");
  fseek(fp, 0L, SEEK_END);
  offset = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  buffer = NULL;
  buffer = (char *)malloc(offset);
  if (!buffer) {
      fprintf(stderr, "Error, cannot allocated buffer.\n");
      return NULL;
  }
  read_size = fread((void *)buffer, offset, 1, fp);

  *buffer_size = offset;

  fclose(fp);
  
  return buffer;
}
