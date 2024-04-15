#include "test.h"

#include <stdlib.h>

#include "expected.h"
#include "actual.h"
#include "config.h"

struct Test* test_create(struct Expected* e, struct Actual* a, struct Config* c)
{
  struct Test* test = malloc(sizeof(struct Test)); 
  test->content = NULL;
  test->expected = e;
  test->actual = a;
  test->config = c;
  return test;
}

void test_destroy(struct Test* test)
{
  free(test->content);
  // potential leak from non-freed string inside expected/acutal/config
  free(test->expected);
  free(test->actual);
  free(test->config);
  free(test);
}
