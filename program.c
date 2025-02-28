#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// TODO: HANDLE CELLS IN QUOTES

int is_valid_number(const char *str) {
    int i = 0, has_decimal = 0;

    if (strcmp(str, "") == 0) return 0;

    if (str[i] == '-') i++;

    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') continue; 
        if (str[i] == '.' && !has_decimal) {
            has_decimal = 1;
            continue;
        }
        return 0;
    }

    return (i > 0);
}

int count_fields(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    int count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    char *field;
    field = strtok(line, ",");
    while (field) {
        count++;
        field = strtok(NULL, ",");
    }

    fclose(file);
    return count;
}

int count_records(const char *filename, int has_header) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    int count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) count++;
    
    fclose(file);
    return has_header? count - 1 : count;
}

double calculate_mean(const char *filename, int field_index) {

    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    double sum = 0.0;
    int count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        char *num_text;
        int col = 0;

        num_text = strtok(line, ",");
        while (num_text) {

            if (col == field_index) {

                // check if number
                if (is_valid_number(num_text)) {
                    sum += atof(num_text);
                    count++;
                }
                break;
            }
            num_text = strtok(NULL, ",");
            col++;
        }
    }

    fclose(file);
    if (count > 0) return (sum / count);
    else exit(EXIT_FAILURE);
}

double calculate_max(const char *filename, int field_index) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    double _max = 0.0;
    int count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        char *num_text;
        int col = 0;

        num_text = strtok(line, ",");
        while (num_text) {

            if (col == field_index) {

                // check if number
                if (is_valid_number(num_text)) {
                    _max = fmax(_max, atof(num_text));
                    count++;
                }
                break;
            }
            num_text = strtok(NULL, ",");
            col++;
        }
    }

    fclose(file);
    if (count > 0)  return _max;
    else exit(EXIT_FAILURE);
}

double calculate_min(const char *filename, int field_index) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    double _min = 0.0;
    int count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        char *num_text;
        int col = 0;

        num_text = strtok(line, ",");
        while (num_text) {

            if (col == field_index) {

                // check if number
                if (is_valid_number(num_text)) {
                    _min = fmin(_min, atof(num_text));
                    count++;
                }
                break;
            }
            num_text = strtok(NULL, ",");
            col++;
        }
    }

    fclose(file);
    if (count > 0) return _min;
    else exit(EXIT_FAILURE);
}

double calculate_mean_by_name(const char *filename, const char *field_name) {
    int idx = get_field_index_by_name(filename, field_name);
    return calculate_mean(filename, idx);
}

double calculate_max_by_name(const char *filename, const char *field_name) {
    int idx = get_field_index_by_name(filename, field_name);
    return calculate_max(filename, idx);
}

double calculate_min_by_name(const char *filename, const char *field_name) {
    int idx = get_field_index_by_name(filename, field_name);
    return calculate_min(filename, idx);
}

void display_records(const char *filename, int field_index, const char *value) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        char *num_text;
        num_text = strtok(line, ",");
        int idx = 0;

        while (num_text) {
            if (idx == field_index && strcmp(value, num_text) == 0) {
                printf("%s", line);
                break;
            }
            idx++;
            num_text = strtok(NULL, ",");
        }
    }
    
    fclose(file);
}

void display_records_by_name(const char *filename, const char *field_name, const char *value) {
    int idx = get_field_index_by_name(filename, field_name);
    display_records(filename, idx, value);
}

int get_field_index_by_name(const char *filename, const char *field_name) {
    FILE *file = fopen(filename, "r");
    if (!file) exit(EXIT_FAILURE);

    char line[2048];
    int idx = -1;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *field;
    field = strtok(line, ",");
    while (field) {
        idx++;
        if (strcmp(field, field_name) == 0) break;
        field = strtok(NULL, ",");
    }

    fclose(file);
    if (idx > -1) return idx;
    else exit(EXIT_FAILURE);
}
