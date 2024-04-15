#include "expected.h"
#include "actual.h"
#include "config.h"

struct Test
{
  struct Expected* expected;
  struct Actual* actual;
  struct Config* config;
  char* content;
};

struct Test* test_create();
void test_destroy(struct Test* test);
