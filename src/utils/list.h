#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct List
{
  size_t size;
  size_t capacity;
  void** elements;
};

struct List* list_create();
void list_append(struct List* l, void* elem);
void list_destroy(struct List* l);

#endif
