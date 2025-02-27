#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>

int is_valid_number(const char *str);

int count_fields(const char *filename);
int count_records(const char *filename, int has_header);

double calculate_mean(const char *filename, int field_index);
double calculate_max(const char *filename, int field_index);
double calculate_min(const char *filename, int field_index);

double calculate_mean_by_name(const char *filename, const char *field_name);
double calculate_max_by_name(const char *filename, const char *field_name);
double calculate_min_by_name(const char *filename, const char *field_name);

void display_records(const char *filename, int field_index, const char *value);
void display_records_by_name(const char *filename, const char *field_name, const char *value);

int get_field_index_by_name(FILE *file, const char *field_name);

#endif 
