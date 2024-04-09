#ifndef SCANNER_H
#define SCANNER_H

/*
  Returns true if the line corresponds to the tag pattern, false if not.
*/
char is_tag(char* line, char* pattern);

/*
  Scan the input file and splits it into a list of Chunks
*/
struct Chunk* scan(char* file, char* pattern);

#endif
