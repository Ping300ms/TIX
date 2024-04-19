#ifndef SCANNER_H
#define SCANNER_H

#include "../utils/list.h"

/*
  Scan the input file and splits it into a list of Chunks
*/
struct List* scan(char* file, char* test_pattern, char* config_pattern);

#endif
