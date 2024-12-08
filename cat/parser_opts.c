#include "parser_opts.h"

void parse_opt(char opt, cat_data *data) {
  switch (opt) {
    case 'b':
      data->flags.b = 1;
      break;

    case 'e':
      data->flags.E = 1;
      data->flags.v = 1;
      break;

    case 'E':
      data->flags.E = 1;
      break;

    case 'n':
      data->flags.n = 1;
      break;

    case 's':
      data->flags.s = 1;
      break;

    case 't':
      data->flags.T = 1;
      data->flags.v = 1;
      break;

    case 'T':
      data->flags.T = 1;
      break;

    case 'v':
      data->flags.v = 1;
      break;

    default:
      data->error = INVALID_FLAG;
      break;
  }
}

void parse_filepath(int argc, int opts_counter, char *argv[], cat_data *data) {
  data->files_count = argc - opts_counter;
  data->files = (char **)malloc(data->files_count * sizeof(char *));
  int file_num = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      data->files[file_num++] = argv[i];
    }
  }
}