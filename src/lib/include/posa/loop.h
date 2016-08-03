#ifndef _LOOP_H_
#define _LOOP_H_

#include <posa/posa.h>
#include <posa/object.h>

typedef void (*posa_handler_cb_t)(posa_t *posa, posa_object_t *object, const unsigned char *buffer, size_t buffer_size, void *user_data);

int posa_loop_from_file(posa_t *posa, char *filename, size_t readsize, posa_handler_cb_t callback, void *user_data);

#endif // _LOOP_H_
