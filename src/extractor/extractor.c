#include <stdlib.h>

#include "../scanner/chunk.h"
#include "../utils/list.h"
#include "test.h"
#include "expected.h"
#include "actual.h"
#include "config.h"

struct Expected* get_expected(struct Chunk* chunk)
{
  // FIXME
  (void)chunk;
  return NULL;
}

struct Actual* get_actual(struct Chunk* chunk)
{
  // FIXME
  (void)chunk;
  return NULL;
}

struct Config* get_config(struct Chunk* chunk)
{
  // FIXME
  (void)chunk;
  return NULL;
}

struct List* extract(struct List* chunk_list)
{
  struct List* test_list = list_create();
  for (size_t i = 0; i < chunk_list->size; i++)
  {
    struct Chunk* chunk = chunk_list->elements[i];

    struct Expected* expected = get_expected(chunk);
    struct Actual* actual = get_actual(chunk);
    struct Config* config = get_config(chunk);

    list_append(test_list, test_create(expected, actual, config));
  }

  return test_list;
}
