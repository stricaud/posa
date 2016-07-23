#ifndef _POS_UTILS_H_
#define _POS_UTILS_H_

#include <stdint.h>

int posa_utils_red_print(char *str);
int posa_utils_blue_print(char *str);
int posa_utils_green_print(char *str);
int posa_utils_yellow_print(char *str);

char *posa_utils_make_buffer_from_file(char *filepath, size_t *buffer_size);

#endif // _POS_UTILS_H_
