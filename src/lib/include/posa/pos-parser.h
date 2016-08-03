#ifndef _POS_PARSER_H_
#define _POS_PARSER_H_

#include <posa/pos-table.h>

int posa_parser_count_lines(char *buffer, size_t bufsize);
pos_table_t *posa_parser_handle_buffer(char *buffer, size_t bufsize, int nblines);

#endif // _POS_PARSER_H_
