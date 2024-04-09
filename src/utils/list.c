#include "list.h"

#include <stdlib.h>

struct List* list_create()
{
  struct List* l = malloc(sizeof(struct List));
  l->size = 0;
  l->capacity = 1;
  l->elements = malloc(sizeof(void*));
  return l;
}

void list_append(struct List* l, void* elem)
{
    
  if (l->size == l->capacity)
  {
    l->capacity *= 2;
    l->elements = realloc(l->elements, sizeof(void*) * l->capacity);
  }
  l->elements[l->size] = elem;
  l->size++;
}

void list_destroy(struct List* l)
{
  for (size_t i = 0; i < l->size; i++)
  {
    free(l->elements[i]);
  }
  free(l->elements);
  free(l);
}

void* list_get(struct List* l, size_t index)
{
  return l->elements[index];
}
