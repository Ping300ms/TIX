#ifndef EXPECTED_H
#define EXPECTED_H

struct Expected
{
  char* expected_out;
  char* expected_err;
  char* expected_code;
  char* command;
  char* title;
};

#endif
