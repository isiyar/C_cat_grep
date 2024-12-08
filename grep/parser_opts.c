#include "parser_opts.h"

grep_data init_data() {
  grep_data data = {.flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  data.error = SUCCESS;
  data.files = NULL;
  data.files_count = 0;
  data.pattern = NULL;
  data.opt_e_value = NULL;
  data.opt_f_value = NULL;
  return data;
}

void parse_opt(char opt, char *optarg, grep_data *data) {
  switch (opt) {
    case 'e':
      if (optarg) {
        data->flags.e = 1;
        data->opt_e_value = optarg;
      } else {
        data->error = INVALID_FLAG_ARGUMENT;
      }
      break;

    case 'f':
      if (optarg) {
        data->flags.f = 1;
        data->opt_f_value = optarg;
        parse_opt_f_value(data);
      } else {
        data->error = INVALID_FLAG_ARGUMENT;
      }
      break;

    case 'i':
      data->flags.i = 1;
      break;

    case 'v':
      data->flags.v = 1;
      break;

    case 'c':
      data->flags.c = 1;
      break;

    case 'l':
      data->flags.l = 1;
      break;

    case 'n':
      data->flags.n = 1;
      break;

    case 'h':
      data->flags.h = 1;
      break;

    case 's':
      data->flags.s = 1;
      break;

    case 'o':
      data->flags.o = 1;
      break;

    default:
      data->error = INVALID_FLAG;
      break;
  }
}

void parse_filepath(int argc, int opts_counter, char *argv[], grep_data *data,
                    int parse_pattern) {
  data->files_count = argc - opts_counter - parse_pattern;
  data->files = (char **)malloc(data->files_count * sizeof(char *));
  int file_num = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-' && strcmp(argv[i - 1], "-e") &&
        strcmp(argv[i - 1], "-f")) {
      if (parse_pattern && data->pattern == NULL) {
        data->pattern = argv[i];
      } else {
        data->files[file_num++] = argv[i];
      }
    }
  }
}

void parse_opt_f_value(grep_data *data) {
  FILE *file = fopen(data->opt_f_value, "r");
  if (file != NULL) {
    int file_length = get_file_length(file);
    data->pattern = (char *)malloc((file_length + 1) * sizeof(char));
    if (data->pattern != NULL) {
      size_t bytes_read = write_buffer(data->pattern, file, file_length);
      if ((long)bytes_read == file_length) {
        data->pattern[file_length] = '\0';
      } else {
        data->error = FAILED_READ_FILE;
      }
    } else {
      data->error = INVALID_BUFFER;
    }
    fclose(file);
  } else {
    data->error = FILE_DOES_NOT_EXIST;
  }
}

int get_file_length(FILE *file) {
  int result;
  fseek(file, 0, SEEK_END);
  result = ftell(file);
  fseek(file, 0, SEEK_SET);
  return result;
}

size_t write_buffer(char *buffer, FILE *file, int file_length) {
  return fread(buffer, 1, file_length, file);
}