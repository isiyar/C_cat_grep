#ifndef PARSER_OPTS_H
#define PARSER_OPTS_H

#include <getopt.h>
#include <stdlib.h>

typedef enum {
  SUCCESS,
  INVALID_FLAG,
  FILE_DOES_NOT_EXIST,
  INVALID_BUFFER,
  FAILED_READ_FILE,
} cat_error;

typedef struct {
  int b, E, v, n, s, T;
} cat_opts;

typedef struct {
  cat_opts flags;
  int files_count;
  char **files;
  int lines_count;
  cat_error error;
} cat_data;

void parse_opt(char opt, cat_data *data);
void parse_filepath(int argc, int opts_counter, char *argv[], cat_data *data);

#endif