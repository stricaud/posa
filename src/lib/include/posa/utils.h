#ifndef _POS_UTILS_H_
#define _POS_UTILS_H_

#include <stdint.h>

int _posa_utils_color_printf(char *colorseq, char *fmt, ...);
#define posa_utils_red_printf(f, ...) \
  _posa_utils_color_printf("\033[1;31m", f, ##__VA_ARGS__)
#define posa_utils_blue_printf(f, ...) \
  _posa_utils_color_printf("\033[1;34m", f, ##__VA_ARGS__)
#define posa_utils_green_printf(f, ...) \
  _posa_utils_color_printf("\033[1;32m", f, ##__VA_ARGS__)
#define posa_utils_yellow_printf(f, ...) \
  _posa_utils_color_printf("\033[1;33m", f, ##__VA_ARGS__)


char *posa_utils_make_buffer_from_file(char *filepath, size_t *buffer_size);

#endif // _POS_UTILS_H_
