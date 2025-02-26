#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fields_amount(FILE *file);
int rows_amount(FILE *file, int use_header);
double min_in_field(FILE *file, int field, int use_header, char *header_field);
double max_in_field(FILE *file, int field, int use_header, char *header_field);
double mean_of_field(FILE *file, int field, int use_header, char *header_field);
void records_print(FILE *file, int field, char *value, int use_header, char *header_field);
int is_header(char *line);
int get_field_index(char *header_line, char *field_name);

int main(int argc, char *argv[])
{
    char *filename = NULL;
    int use_header = 0;
    char *header_field = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            use_header = 1;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            filename = argv[++i];
            FILE *file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("open file failed.\n");
                return EXIT_FAILURE;
            }
            printf("%d\n", fields_amount(file));
            fclose(file);
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            filename = argv[++i];
            FILE *file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("open file failed.\n");
                return EXIT_FAILURE;
            }
            printf("%d\n", rows_amount(file, use_header));
            fclose(file);
        }
        else if (strcmp(argv[i], "-min") == 0)
        {
            if (i + 1 < argc)
            {
                int min_field = atoi(argv[++i]);
                if (use_header)
                {
                    header_field = argv[i];
                }
                filename = argv[++i];
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("open file failed.\n");
                    return EXIT_FAILURE;
                }
                printf("%.2f\n", min_in_field(file, min_field, use_header, header_field));
                fclose(file);
            }
            else
            {
                printf("-min needs one argument.\n");
                return EXIT_FAILURE;
            }
        }
        else if (strcmp(argv[i], "-max") == 0)
        {
            if (i + 1 < argc)
            {
                int max_field = atoi(argv[++i]);
                if (use_header)
                {
                    header_field = argv[i];
                }
                filename = argv[++i];
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("open file failed.\n");
                    return EXIT_FAILURE;
                }
                printf("%.2f\n", max_in_field(file, max_field, use_header, header_field));
                fclose(file);
            }
            else
            {
                printf("-max needs one argument.\n");
                return EXIT_FAILURE;
            }
        }
        else if (strcmp(argv[i], "-mean") == 0)
        {
            if (i + 1 < argc)
            {
                int mean_field = atoi(argv[++i]);
                if (use_header)
                {
                    header_field = argv[i];
                }
                filename = argv[++i];
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("open file failed.\n");
                    return EXIT_FAILURE;
                }
                printf("%.2f\n", mean_of_field(file, mean_field, use_header, header_field));
                fclose(file);
            }
            else
            {
                printf("-mean needs one argument.\n");
                return EXIT_FAILURE;
            }
        }
        else if (strcmp(argv[i], "-records") == 0)
        {
            if (i + 2 < argc)
            {
                int records_field = atoi(argv[++i]);
                char *records_value = argv[++i];
                if (use_header)
                {
                    header_field = argv[i];
                }
                filename = argv[++i];
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("open file failed.\n");
                    return EXIT_FAILURE;
                }
                records_print(file, records_field, records_value, use_header, header_field);
                fclose(file);
            }
            else
            {
                printf("-records needs two arguments.\n");
                return EXIT_FAILURE;
            }
        }
        else
        {
            filename = argv[i];
        }
    }

    if (filename == NULL)
    {
        printf("you have to specify a file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// -f function: count the number of fields of the first line
int fields_amount(FILE *file)
{
    size_t len = 0;
    char *line = NULL;
    getline(&line, &len, file);
    fseek(file, 0, SEEK_SET);
    // fields amount is the number of commas + 1
    int count = 1;
    for (char *ptr = line; *ptr != '\0'; ptr++)
    {
        if (*ptr == ',')
            count++;
    }
    free(line);
    return count;
}

// check if the line is a header
int is_header(char *line)
{
    for (char *ptr = line; *ptr != '\0'; ptr++)
    {
        if ((*ptr < '0' || *ptr > '9') && *ptr != ',' && *ptr != '\n')
        {
            return 1;
        }
    }
    return 0;
}

// -r function: count the number of rows
// if the first line is a header, it should be ignored
int rows_amount(FILE *file, int use_header)
{
    size_t len = 0;
    char *line = NULL;
    int count = 0;

    // check if the first line is a header
    if (getline(&line, &len, file) != -1)
    {
        if (use_header && is_header(line))
        {
            count = 0;
        }
        else
        {
            count = 1;
        }
    }

    // this start at the second line because the first line is a header
    // count the amount of lines
    while (getline(&line, &len, file) != -1)
    {
        count++;
    }
    fseek(file, 0, SEEK_SET);
    free(line);

    return count;
}

// -h function: get the index of the specified field
int get_field_index(char *header_line, char *field_name)
{
    char *index = strtok(header_line, ",");
    for (int i = 0; index != NULL; i++)
    {
        if (strcmp(index, field_name) == 0)
        {
            return i;
        }
        index = strtok(NULL, ",");
    }
    return EXIT_FAILURE; // field not found
}

// -min function: find the minimum value in the specified field
double min_in_field(FILE *file, int field, int use_header, char *header_field)
{
    size_t len = 0;
    char *line = NULL;
    double min = 0;
    int first = 1;
    int has_header = 0;

    if (getline(&line, &len, file) != -1)
    {
        has_header = is_header(line);
        if (use_header)
        {
            field = get_field_index(line, header_field);
            if (field == -1)
            {
                printf("Invalid field name.\n");
                free(line);
                return EXIT_FAILURE;
            }
        }
    }

    if (!has_header)
    {
        fseek(file, 0, SEEK_SET);
    }

    while (getline(&line, &len, file) != -1)
    {
        // spilt the line by comma
        char *index = strtok(line, ",");
        for (int i = 0; index != NULL; i++)
        {
            if (i == field)
            {
                double value = atof(index);

                if (first || value <= min)
                {
                    // set the first value as the minimum
                    min = value;
                    first = 0;
                }
                break;
            }
            index = strtok(NULL, ",");
        }
    }
    fseek(file, 0, SEEK_SET);
    free(line);
    return min;
}

// -max function: find the maximum value in the specified field
double max_in_field(FILE *file, int field, int use_header, char *header_field)
{
    size_t len = 0;
    char *line = NULL;
    double max = 0;
    int first = 1;
    int has_header = 0;

    if (getline(&line, &len, file) != -1)
    {
        has_header = is_header(line);
        if (use_header)
        {
            field = get_field_index(line, header_field);
            if (field == -1)
            {
                printf("Invalid field name.\n");
                free(line);
                return EXIT_FAILURE;
            }
        }
    }

    if (!has_header)
    {
        fseek(file, 0, SEEK_SET);
    }

    while (getline(&line, &len, file) != -1)
    {
        char *index = strtok(line, ",");
        for (int i = 0; index != NULL; i++)
        {
            if (i == field)
            {
                double value = atof(index);
                // set the first value as the maximum
                if (first || value > max)
                {
                    max = value;
                    first = 0;
                }
                break;
            }
            index = strtok(NULL, ",");
        }
    }
    fseek(file, 0, SEEK_SET);
    free(line);
    return max;
}

// -mean function: find the mean value in the specified field
double mean_of_field(FILE *file, int field, int use_header, char *header_field)
{
    size_t len = 0;
    char *line = NULL;
    double sum = 0;
    int count = 0;
    int has_header = 0;

    if (getline(&line, &len, file) != -1)
    {
        has_header = is_header(line);
        if (use_header)
        {
            field = get_field_index(line, header_field);
            if (field == -1)
            {
                printf("Invalid field name.\n");
                free(line);
                return EXIT_FAILURE;
            }
        }
    }

    if (!has_header)
    {
        fseek(file, 0, SEEK_SET);
    }

    while (getline(&line, &len, file) != -1)
    {
        char *index = strtok(line, ",");
        for (int i = 0; index != NULL; i++)
        {
            if (i == field)
            {
                // sum of the values in this specific field
                sum += atof(index);
                count++;
                break;
            }
            index = strtok(NULL, ",");
        }
    }
    fseek(file, 0, SEEK_SET);
    free(line);
    
    if (count == 0)
    {
        return 0;
    }
    return sum / count;
}

// -records function: print the records that have the specified value in the specified field
void records_print(FILE *file, int field, char *value, int use_header, char *header_field)
{
    size_t len = 0;
    char *line = NULL;
    int has_header = 0;

    if (getline(&line, &len, file) != -1)
    {
        has_header = is_header(line);
        if (use_header)
        {
            field = get_field_index(line, header_field);
            if (field == -1)
            {
                printf("Invalid field name.\n");
                free(line);
                return;
            }
        }
    }

    if (!has_header)
    {
        fseek(file, 0, SEEK_SET);
    }

    while (getline(&line, &len, file) != -1)
    {
        char *index = strtok(line, ",");
        for (int i = 0; index != NULL; i++)
        {
            if (i == field && strcmp(index, value) == 0)
            {
                printf("%s", line);
                break;
            }
            index = strtok(NULL, ",");
        }
    }
    fseek(file, 0, SEEK_SET);
    free(line);
}