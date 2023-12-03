#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advent.h"

// perform python-like split on string
char** split(const char* str, const char delim)
{
    // get number of instances
    size_t i;
    for (i=0; str[i]; str[i]=='.' ? i++ : *str++);

    // generate list
    char** list = malloc(i * sizeof(char*));
    char* token = strtok(str, &delim);
    while (token != NULL)
    {
        *list++ = token;
        token = strtok(NULL, &delim);
    }

    return list;
}