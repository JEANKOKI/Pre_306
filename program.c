#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_fields(const char *filename) {
    return 0;
}

int count_records(const char *filename, int has_header) {
    return 0;
}

double calculate_mean(const char *filename, int field_index) {
    return 0.0;
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
