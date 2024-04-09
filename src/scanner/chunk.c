#include "chunk.h"

#include <stdlib.h>

struct Chunk* chunk_create()
{
  struct Chunk* c = malloc(sizeof(struct Chunk));
  c->tags = linelist_create();
  c->content = linelist_create();
  c->next = NULL;
  return c;
}

void chunk_destroy(struct Chunk* c)
{
  linelist_destroy(c->tags);
  linelist_destroy(c->content);
  if (c->next)
    chunk_destroy(c->next);
  free(c);
}
