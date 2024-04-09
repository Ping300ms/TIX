#define _POSIX_C_SOURCE 200809L

#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "chunk.h"
#include "../utils/list.h"

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
    {
        regfree(&regex);
        return 1;
    }
    else if (reti == REG_NOMATCH)
    {
        regfree(&regex);
        return 0;
    }
    else 
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "TIX: Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        exit(EXIT_FAILURE);
    }
}

struct List* scan(char* file, char* pattern)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char is_tag_before = 0;

    struct List* chunk_list = list_create();

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "TIX: Failed to open %s", file);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {        
        struct Chunk* current = chunk_list->elements[chunk_list->size - 1];
        char* to_append = malloc(sizeof(char) * len);
        strcpy(to_append, line);
        
        if (is_tag(line, pattern))
        {
            /*
                If the previous line was not a tag, it means the current chunk
                is finished so we create a new one
            */
            if (!is_tag_before)
            {
                list_append(chunk_list, chunk_create());
                current = chunk_list->elements[chunk_list->size - 1];
            }

            list_append(current->tags, to_append);
            is_tag_before = 1;
        }
        else
        {
            list_append(current->content, to_append);
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
    
    struct List* c = scan("test.txt", "bonsoir");


    for (size_t i = 0; i < c->size; i++)
    {
        struct Chunk* ch = c->elements[i];
        printf("tags:\n");
        for (size_t j = 0; j < ch->tags->size; j++)
            printf("%s\n", (char*) ch->tags->elements[j]);
        printf("\ncontent;\n");
        for (size_t j = 0; j < ch->content->size; j++)
            printf("%s\n", (char*) ch->content->elements[j]);
        printf("\n\n");
    }

    for (size_t i = 0; i < c->size; i++)
        chunk_destroy(c->elements[i]);
    list_destroy(c);
}
*/
