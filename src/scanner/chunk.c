#include "chunk.h"

#include <stdlib.h>

struct Chunk* chunk_create()
{
  struct Chunk* c = malloc(sizeof(struct Chunk));
  c->tags = list_create();
  c->content = list_create();
  c->is_config = 0;
  return c;
}

void chunk_destroy(struct Chunk* c)
{
  list_destroy(c->tags);
  list_destroy(c->content);
  free(c);
}
