#include "expected.h"
#include "actual.h"
#include "config.h"

struct Test
{
  Expected expected;
  Actual actual;
  Config config;
  char* content;
};
