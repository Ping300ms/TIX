#define _POSIX_C_SOURCE 200809L

#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "chunk.h"
#include "linelist.h"

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

    char is_tag_before = 0;

    struct Chunk* chunk_list = chunk_create();
    struct Chunk* chunk_pointer = chunk_list;

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
            /*
                If the previous line was not a tag, it means the current chunk
                is finished so we create a new one
            */
            if (!is_tag_before)
            {
                chunk_pointer->next = chunk_create();
                chunk_pointer = chunk_pointer->next;
            }
            linelist_append(chunk_pointer->tags, line);
            is_tag_before = 1;
        }
        else
        {
            linelist_append(chunk_pointer->content, line);
            is_tag_before = 0;    
        }
    }
    fclose(fp);
    free(line);
    return chunk_list;
}

/*
#include <stdio.h>
int main(int argc, char** argv)
{
    (void)argc;
    (void) argv;
    
    struct Chunk* c = scan("test.txt", "bonsoir");
    struct Chunk* c2 = c;

    while (c2)
    {
        printf("tags:\n");
        for (size_t i = 0; i < c2->tags->size; i++)
            printf("%s\n", c2->tags->lines[i]);
        printf("content:\n");
        for (size_t i = 0; i < c2->content->size; i++)
            printf("%s\n", c2->content->lines[i]);
        c2 = c2->next;
    }
}
*/
