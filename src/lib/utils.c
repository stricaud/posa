#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int posa_utils_red_print(char *str)
{
  printf("\033[1;31m%s\033[0m", str);
}

int posa_utils_blue_print(char *str)
{
  printf("\033[1;34m%s\033[0m", str);
}

int posa_utils_green_print(char *str)
{
  printf("\033[1;32m%s\033[0m", str);
}

int posa_utils_yellow_print(char *str)
{
  printf("\033[1;33m%s\033[0m", str);
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
