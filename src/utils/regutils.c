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
    if (reti == 1)
    {
        fprintf(stderr, "TIX: Could not compile tag delimiters\n");
        exit(EXIT_FAILURE);
    }
    reti = regexec(&regex, string, 0, NULL, 0);
    if (reti == 0)
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
  regex_t *regex = (regex_t*)malloc(sizeof(regex_t));
  regmatch_t *match;

  
  if (regcomp(regex, pattern,REG_EXTENDED|REG_NEWLINE))
  {
      fprintf(stderr, "TIX: Could not compile tag delimiters\n");
      exit(EXIT_FAILURE);
  }
  match = (regmatch_t*)malloc(sizeof(regmatch_t)*(regex->re_nsub+1));

  
  if(regexec(regex, string, regex->re_nsub+1, match, 0))
  {
    fprintf(stderr, "TIX: No match in header\n");
    exit(EXIT_FAILURE);
  }

  
  if(match[0].rm_so == -1)
  {
    fprintf(stderr, "TIX: No");
  }
  int start = match[0].rm_so;
  int finish = match[0].rm_eo;
  char* res = (char*)malloc(((finish-start) + 1));
  sprintf(res, "%.*s", finish-start , string + start);
  regfree(regex);

  return res;
}

/*int main()
{
  char* a = "aagezo4556rgiperugbneroifejgfnerbons9,0ooooiroebzerrzberzer";
  //char * r = regex_get(a, "([0-9]+)");
  //printf("%s", r);
  a = "Bonsoir partiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii !!!";
  char *r = regex_get(a, "parti+ !");
  printf("%s", r);
  //r = regex_get(a, "ti");
  //printf("%s", r);

  /*printf("%d\n", regex_check(a, "i*"));
  printf("%d\n", regex_check(a, "y.*"));
  printf("%d\n", regex_check(a, "x"));

}*/
