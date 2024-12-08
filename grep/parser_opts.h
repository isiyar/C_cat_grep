#ifndef PARSER_OPTS_H
#define PARSER_OPTS_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  SUCCESS,
  INVALID_FLAG,
  INVALID_FLAG_ARGUMENT,
  FILE_DOES_NOT_EXIST,
  INVALID_BUFFER,
  FAILED_READ_FILE
} grep_error;

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
} grep_opts;

typedef struct {
  grep_opts flags;
  int files_count;
  char **files;
  char *pattern;
  char *opt_e_value;
  char *opt_f_value;
  grep_error error;
} grep_data;

grep_data init_data();
void parse_opt(char opt, char *optarg, grep_data *data);
void parse_filepath(int argc, int opts_counter, char *argv[], grep_data *data,
                    int parse_pattern);
void parse_opt_f_value(grep_data *data);
int get_file_length(FILE *file);
size_t write_buffer(char *buffer, FILE *file, int file_length);

#endif