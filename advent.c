#include <stdio.h>
#include <stdlib.h>
#include "advent.h"


char** split(const char* str, const char delim)
{
    // get number of instances
    size_t i;
    for (i=0; str[i]; str[i]=='.' ? i++ : *str++);

    char** list = malloc(i * sizeof(char*));
    return list;
}