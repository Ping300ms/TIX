#ifndef LINELIST_H
#define LINELIST_H

#include <stddef.h>

struct Linelist
{
  size_t size;
  size_t capacity;
  char** lines;
};

struct Linelist* linelist_create();
void linelist_append(struct Linelist* l, char* line);
void linelist_destroy(struct Linelist* l);

#endif
