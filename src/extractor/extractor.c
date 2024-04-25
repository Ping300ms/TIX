#include <stdlib.h>
#include <stdio.h>

#include "../scanner/chunk.h"
#include "../utils/list.h"
#include "../utils/regutils.h"
#include "test.h"
#include "expected.h"
#include "actual.h"
#include "config.h"

struct Expected* get_expected(char* tag)
{
  // FIXME DO THE REGEX
  struct Expected* expected = malloc(sizeof(struct Expected));
  expected->expected_out = regex_get(tag, "");
  expected->expected_err = regex_get(tag, "");
  expected->expected_code = regex_get(tag, "");
  expected->command = regex_get(tag, "");
  expected->title = regex_get(tag, "");
  return expected;
}

struct Actual* get_actual()
{
  struct Actual* actual = malloc(sizeof(struct Actual));
  actual->actual_out = NULL;
  actual->actual_err = NULL;
  actual->actual_code = NULL;
  return actual;
}

struct Config* get_config(struct List* chunk_list)
{
  // FIXME DO THE REGEX
  char* tag = NULL;
  for (size_t i = 0 ; i < chunk_list->size; i++)
  {
    if (((struct Chunk*)chunk_list->elements[i])->is_config)
      tag = chunk_list->elements[i];
  }
  if (tag == NULL)
    fprintf(stderr, "TIX: No config tag found");
  
  struct Config* config = malloc(sizeof(struct Config));
  config->executable = regex_get(tag, "");
  config->file_extension = regex_get(tag, "");
  config->exec_path = regex_get(tag, "");
  return config;
}

struct List* extract(struct List* chunk_list)
{
  struct Config* config = get_config(chunk_list);
  struct List* test_list = list_create();
  for (size_t i = 0; i < chunk_list->size; i++)
  {
    struct Chunk* chunk = chunk_list->elements[i];
    for (size_t j = 0; j < chunk->tags->size; j++)
    {
      struct Expected* expected = get_expected(chunk->tags->elements[j]);
      struct Actual* actual = get_actual();
      list_append(test_list, test_create(expected, actual, config));
    }
  }

  return test_list;
}
