#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

#include "parser_opts.h"

void read_file(char *filepath, int file_index, cat_data *data);
int get_file_length(FILE *file);
size_t write_buffer(char *buffer, FILE *file, int file_length);
void print_file_content(char *buffer, int file_length, cat_data *data,
                        int file_index);

#endif