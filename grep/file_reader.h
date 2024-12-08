#ifndef FILE_READER_H
#define FILE_READER_H
#define _GNU_SOURCE

#include <regex.h>
#include <string.h>

#include "parser_opts.h"

void read_file(char *filepath, int file_index, grep_data *data, regex_t regex);
void find_regex_match(char *line, regex_t *regex, grep_data *data,
                      int *matching_lines_counter, int all_lines_counter,
                      int *is_file_find, int file_index);
void print_filedata(grep_data *data, int file_index, int all_lines_counter);
#endif