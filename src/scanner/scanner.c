#define _POSIX_C_SOURCE 200809L

#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "chunk.h"

char is_tag(char* line, char* pattern)
{
    regex_t regex;
    int reti;
    char msgbuf[100];
    
    reti = regcomp(&regex, pattern, 0);
    if (reti)
    {
        fprintf(stderr, "TIX: Could not compile tag delimiters\n");
        exit(EXIT_FAILURE);
    }
    
    reti = regexec(&regex, line, 0, NULL, 0);
    if (!reti)
        return 1;
    else if (reti == REG_NOMATCH)
        return 0;
    else 
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "TIX: Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }    
}

struct Chunk* scan(char* file, char* pattern)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    struct Chunk* chunk_list = malloc(sizeof(struct Chunk));
    chunk_list->next = NULL;

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "TIX: Failed to open %s", file);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (is_tag(line, pattern))
        {
            // TODO if line is a tag
        }
        else
        {
            // TODO if it isn't
        }
    }

    fclose(fp);
    free(line);

    return chunk_list;
}
