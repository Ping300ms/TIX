#ifndef CHUNK_H
#define CHUNK_H

#include "../utils/list.h"

struct Chunk
{
  /*
    Stores every tags/content pair of a file.
    Simplifies greatly the work of the extractor.
  */
  struct List* tags;
  struct List* content;
  char is_config;
  /*
    Chunks are in the form of a linked list to simplify their allocation in
    the scanner.
  */
};

struct Chunk* chunk_create();
void chunk_destroy(struct Chunk* c);

#endif
