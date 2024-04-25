#ifndef DISPLAYER_H
#define DISPLAYER_H

#include "../utils/list.h"

struct Summary
{
  size_t pass;
  size_t fail;
  size_t crash;
};

enum Color
{
  RED,
  GREEN,
  YELLOW,
  BLUE,
  DEFAULT
};

void display(struct List* test_list, char* file_name, char is_colored);

#endif
