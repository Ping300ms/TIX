#include "regutils.h"

#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char regex_check(char* string, char* pattern)
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
    reti = regexec(&regex, string, 0, NULL, 0);
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

char* regex_get(char* string, char* pattern)
{
  // FIXME
  regex_t regex;
  regmatch_t* match = NULL;
  int reti;
  
  reti = regexec(&regex, pattern, 1, match, 0);
  if(reti)
  {
    fprintf(stderr, "TIX: No match in header\n");
    exit(EXIT_FAILURE);
  }
   
  int i = 0;
  if(match[i].rm_so == -1)
  {
    fprintf(stderr, "TIX: No");
  }
  int start = match[i].rm_so;
  int finish = match[i].rm_eo;
  char* res = malloc(sizeof(char) * (finish - start + 1));
  sprintf(res, "%.*s", (finish - start), string + start);
  return res;
}

/*
int main()
{
  char* a = "Bonsoir pariiiiiiiiiis !!!";
  printf("%s\n", regex_get(a, "i*"));
}
  */
