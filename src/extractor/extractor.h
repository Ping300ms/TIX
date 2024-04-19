#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "config.h"
#include "expected.h"
#include "actual.h"

struct Expected* get_expected(char* tag);
struct Actual* get_actual();
struct Config* get_config(struct List* chunk_list);
struct List* extract(struct List* chunk_list);

#endif
