#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_valid_number(const char *str) {
    int i = 0, has_decimal = 0;

    //TODO: HANDLE WHITESPACE
    // HANDLE EMPTY CELL

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
    return 0;
}

int count_records(const char *filename, int has_header) {
    return 0;
}

double calculate_mean(const char *filename, int field_index) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        exit(EXIT_FAILURE);
    }

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
    if (count > 0) {
        return (sum / count);
    } else {
        exit(EXIT_FAILURE);
    }
}

double calculate_max(const char *filename, int field_index) {
    return 0.0;
}

double calculate_min(const char *filename, int field_index) {
    return 0.0;
}

double calculate_mean_by_name(const char *filename, const char *field_name) {
    return 0.0;
}

double calculate_max_by_name(const char *filename, const char *field_name) {
    return 0.0;
}

double calculate_min_by_name(const char *filename, const char *field_name) {
    return 0.0;
}

void display_records(const char *filename, int field_index, const char *value) {
    return;
}

void display_records_by_name(const char *filename, const char *field_name, const char *value) {
    return;
}

int get_field_index_by_name(FILE *file, const char *field_name) {
    return -1;
}
