#ifndef _IO_H_
#define _IO_H_

#include <posa/posa.h>

int posa_io_open(posa_t *posa, char *posa_desc_filepath);
int posa_io_close(posa_t *posa);

#endif // _IO_H_
