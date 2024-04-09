#include "linelist.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Linelist* linelist_create()
{
  struct Linelist* l = malloc(sizeof(struct Linelist));
  l->size = 0;
  l->capacity = 1;
  l->lines = malloc(sizeof(char*));
  return l;
}

void linelist_append(struct Linelist* l, char* line)
{
  if (l->size == l->capacity)
  {
    l->capacity *= 2;
    l->lines = realloc(l->lines, sizeof(char*) * l->capacity);
  }
  l->lines[l->size] = malloc(sizeof(char) * (strlen(line) + 1));
  sprintf(l->lines[l->size], "%s", line);
  l->size++;
}

void linelist_destroy(struct Linelist* l)
{
  for (size_t i = 0; i < l->size; i++)
  {
    free(l->lines[i]);
  }
  free(l->lines);
  free(l);
}
