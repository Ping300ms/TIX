#ifndef SCANNER_H
#define SCANNER_H

#include "../utils/list.h"

/*
  Returns true if the line corresponds to the tag pattern, false if not.
*/
char is_tag(char* line, char* pattern);

/*
  Scan the input file and splits it into a list of Chunks
*/
struct List* scan(char* file, char* pattern);

#endif
