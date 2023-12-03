#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <advent.h>

typedef struct max
{
    int red;
    int green;
    int blue;
} Max;

int one(FILE *fp)
{
    char *line = NULL;
    size_t len;
    Max maxes = {12, 13, 14};

    int total = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int x = 0;
        size_t num_tokens;
        strip(line);

        // get game number
        char **g = split(line, ":", &num_tokens);
        char const *n = split(g[0], " ", &num_tokens)[1];

        // get list of turns
        size_t num_turns;
        char **t = split(g[1], ";", &num_turns);
        // iterate through all turns
        for (size_t i = 0; i < num_turns; ++i)
        {
            // for each enum, check the letters
            size_t num_enums;
            char **e = split(strip(t[i]), ",", &num_enums);
            for (size_t j = 0; j < num_enums; ++j)
            {
                // get key value
                char const *i = split(strip(e[j]), " ", &num_tokens)[0];
                char const *v = split(strip(e[j]), " ", &num_tokens)[1];

                // check if conditions are met
                int pass = 1;
                if (strcmp(v, "red") == 0 && atoi(i) > maxes.red)
                    pass = 0;
                else if (strcmp(v, "green") == 0 && atoi(i) > maxes.green)
                    pass = 0;
                else if (strcmp(v, "blue") == 0 && atoi(i) > maxes.blue)
                    pass = 0;

                if (!pass)
                    ++x;
            }
        }

        // if x==0, all passed, add to total
        if (x == 0)
            total += atoi(n);
    }
    return total;
}

int two(FILE *fp)
{
    char *line = NULL;
    size_t len;

    int total = 0;
    while (getline(&line, &len, fp) != -1)
    {
        strip(line);
        Max maxes = {0, 0, 0};

        // get list of turns
        size_t num_turns;
        char const *g = split(line, ":", NULL)[1];
        char **t = split(g, ";", &num_turns);
        // iterate through all turns
        for (size_t i = 0; i < num_turns; ++i)
        {
            // for each enum, check the letters
            size_t num_enums;
            char **e = split(strip(t[i]), ",", &num_enums);
            for (size_t j = 0; j < num_enums; ++j)
            {
                // get key value
                char const *k = split(strip(e[j]), " ", NULL)[0];
                char const *v = split(strip(e[j]), " ", NULL)[1];

                // get the power
                if (strcmp(v, "red") == 0)
                    maxes.red = MAX(atoi(k), maxes.red);
                else if (strcmp(v, "green") == 0)
                    maxes.green = MAX(atoi(k), maxes.green);
                else if (strcmp(v, "blue") == 0)
                    maxes.blue = MAX(atoi(k), maxes.blue);
            }
        }
        total += (maxes.blue * maxes.green * maxes.red);
    }
    return total;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return 0;
}