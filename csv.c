#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("invalid amount of arguemets \n");
        return EXIT_FAILURE;
    }

    int argsNoFile = argc - 1;         // argc - 1
    char *filename = argv[argsNoFile]; // since the filename is always at the end of arguement

    // data to store before computation
    int *flags = malloc(7 * sizeof(int));
    flags[0] = 0;          // stores header specification
    int flags_indexer = 1; // maintains order of input

    // flag constants
    int COUNT_FIELDS_FLAG = 2;
    int COUNT_RECORDS_FLAG = 3;
    int MAX_FLAG = 4;
    int MIN_FLAG = 5;
    int MEAN_FLAG = 6;
    int GET_RECORDS_FLAG = 7;

    // input data
    char *max_in = NULL;
    char *min_in = NULL;
    char *mean_in = NULL;
    char *records_in_1 = NULL;
    char *records_in_2 = NULL;

    // {1:-1} Iterate from after the program name to before the filename (already stored)
    // if -h can be anywhere in the arguments, we must check all args before computation
    for (int i = 1; i < argsNoFile; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            flags[0] = 1;
            continue;
        }

        else if (strcmp(argv[i], "-f") == 0)
        {
            flags[flags_indexer++] = COUNT_FIELDS_FLAG;
            continue;
        }

        else if (strcmp(argv[i], "-r") == 0)
        {
            flags[flags_indexer++] = COUNT_RECORDS_FLAG;
            continue;
        }

        else if (strcmp(argv[i], "-max") == 0)
        {
            flags[flags_indexer++] = MAX_FLAG;
            if (i + 1 < argsNoFile)
            {
                max_in = argv[++i]; // increment i, then store. (skips over input data in succeeding iteration)
            }
            else
            {
                // ERROR!
                return EXIT_FAILURE;
            }
            continue;
        }

        else if (strcmp(argv[i], "-min") == 0)
        {
            flags[flags_indexer++] = MIN_FLAG;
            if (i + 1 < argsNoFile)
            {
                min_in = argv[++i]; // increment i, then store. (skips over input data in succeeding iteration)
            }
            else
            {
                // ERROR!
                return EXIT_FAILURE;
            }
            continue;
        }

        else if (strcmp(argv[i], "-mean") == 0)
        {
            flags[flags_indexer++] = MEAN_FLAG;
            if (i + 1 < argsNoFile)
            {
                mean_in = argv[++i]; // increment i, then store. (skips over input data in succeeding iteration)
            }
            else
            {
                // ERROR!
                return EXIT_FAILURE;
            }
            continue;
        }

        else if (strcmp(argv[i], "-records") == 0)
        {
            flags[flags_indexer++] = GET_RECORDS_FLAG;
            if (i + 1 < argsNoFile)
            {
                records_in_1 = argv[++i]; // increment i, then store. (skips over input data in succeeding iteration)
            }
            else
            {
                // ERROR!
                return EXIT_FAILURE;
            }
            if (i + 1 < argsNoFile)
            {
                records_in_2 = argv[++i]; // increment i, then store. (skips over input data in succeeding iteration)
            }
            else
            {
                // ERROR!
                return EXIT_FAILURE;
            }
            continue;
        }
    }

    // if header is specified, compute by name...
    // else, by index.
    if (flags[0])
    {
        // assess the flags in order
        for (int i = 1; i < 7; i++)
        {
            if (flags[i] == COUNT_FIELDS_FLAG)
            {

                count_fields(filename);
                continue;
            }
            if (flags[i] == COUNT_RECORDS_FLAG)
            {
                count_records(filename, 1);
                continue;
            }
            if (flags[i] == MAX_FLAG)
            {
                calculate_max_by_name(filename, max_in);
                continue;
            }
            if (flags[i] == MIN_FLAG)
            {
                calculate_min_by_name(filename, min_in);
                continue;
            }
            if (flags[i] == MEAN_FLAG)
            {
                calculate_mean_by_name(filename, mean_in);
                continue;
            }
            if (flags[i] == GET_RECORDS_FLAG)
            {
                display_records_by_name(filename, records_in_1, records_in_2);
                continue;
            }
        }
    }
    else
    {
        // assess the flags in order
        for (int i = 1; i < 7; i++)
        {
            if (flags[i] == COUNT_FIELDS_FLAG)
            {
                count_fields(filename);
                continue;
            }
            if (flags[i] == COUNT_RECORDS_FLAG)
            {
                count_records(filename, 0);
                continue;
            }
            if (flags[i] == MAX_FLAG)
            {
                calculate_max(filename, atoi(max_in));
                continue;
            }
            if (flags[i] == MIN_FLAG)
            {
                calculate_min(filename, atoi(min_in));
                continue;
            }
            if (flags[i] == MEAN_FLAG)
            {
                calculate_mean(filename, atoi(mean_in));
                continue;
            }
            if (flags[i] == GET_RECORDS_FLAG)
            {
                display_records(filename, atoi(records_in_1), records_in_2);
                continue;
            }
        }
    }

    return EXIT_SUCCESS;
}
