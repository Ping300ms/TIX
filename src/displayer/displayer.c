#include "displayer.h"

#include <stdlib.h>
#include <stdio.h>

#include "../utils/list.h"
#include "../extractor/test.h"

char* get_color(enum Color c)
{
  char* color = "";
  switch (c) 
  {
    case RED:
      color = "\033[0;31m";
      break;
    case YELLOW:
      color = "\033[0;33m";
      break;
    case GREEN:
      color = "\033[0;32m";
      break;
    case BLUE:
      color = "\033[0;34m";
      break;
    default:
      color = "\033[0;0m";
  }
  return color;
}

void display_title(struct Test* test, char is_colored)
{
  char* blue = "";
  char* white = "";
  if (is_colored)
  {
    blue = get_color(BLUE);
    white = get_color(DEFAULT);
  }
  printf("[%s%s%s]\n", blue, test->expected->title,white);
}

void display_stdout(struct Test* test, char is_colored)
{
  //TODO
}

void display_error(struct Test* test, char is_colored)
{
  //TODO  
}

void display_code(struct Test* test, char is_colored)
{
  //TODO
}

void display_test(struct Test* test, char is_colored)
{
  display_title(test, is_colored);
  display_stdout(test, is_colored);
  display_error(test, is_colored);
  display_code(test, is_colored);
}

void display_summary(struct Summary* summary, char is_colored)
{
  char* yellow = "";
  char* red = "";
  char* white = "";
  if (is_colored)
  {
    yellow = get_color(YELLOW);
    red = get_color(RED);
    white = get_color(DEFAULT);
  }
  printf("[%sFAILED%s]: %ld\n[%sCRASHED%s]: %ld\n[TOTAL]: %ld",
        red,
        white,
        summary->fail,
        yellow,
        white,
        summary->crash,
        summary->crash + summary->fail + summary->pass
      );
}

void display(struct List* test_list, char* file_name, char is_colored)
{
  char* blue = "";
  char* white = "";
  if (is_colored)
  {
    blue = get_color(BLUE);
    white = get_color(DEFAULT);
  }
  printf("=======================================[%s%s%s]", blue, file_name, white);
  struct Summary* summary = malloc(sizeof(struct Summary));
  for (size_t i = 0; i < test_list->size; i++)
  {
    display_test(test_list->elements[i], is_colored);
  }
  display_summary(summary, is_colored);
  free(summary);
}
