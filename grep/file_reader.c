#include "file_reader.h"

void read_file(char *filepath, int file_index, grep_data *data, regex_t regex) {
  FILE *file = fopen(filepath, "r");
  if (file != NULL) {
    char *line = NULL;
    size_t len = 0;
    int matching_lines_counter = 0, all_lines_counter = 0, is_file_find = 0;
    while ((getline(&line, &len, file)) != -1 && !is_file_find) {
      all_lines_counter++;
      find_regex_match(line, &regex, data, &matching_lines_counter,
                       all_lines_counter, &is_file_find, file_index);
    }
    if (data->flags.c && !data->flags.l) {
      if (data->files_count > 1) {
        printf("%s:%d\n", filepath, matching_lines_counter);
      } else {
        printf("%d\n", matching_lines_counter);
      }
    }
    fclose(file);
    free(line);
  } else {
    data->error = FILE_DOES_NOT_EXIST;
  }
}

void find_regex_match(char *line, regex_t *regex, grep_data *data,
                      int *matching_lines_counter, int all_lines_counter,
                      int *is_file_find, int file_index) {
  regmatch_t matches[1];
  if (regexec(regex, line, 1, matches, 0) == data->flags.v) {
    if (data->flags.l) {
      printf("%s\n", data->files[file_index]);
      *is_file_find = 1;
    } else if (!data->flags.c) {
      if (data->flags.o) {
        int index = 0;
        while (!regexec(regex, line + index, 1, matches, 0)) {
          int start = matches[0].rm_so + index;
          int end = matches[0].rm_eo + index;
          print_filedata(data, file_index, all_lines_counter);
          printf("%.*s\n", end - start, line + start);
          index = end;
        }
      } else {
        print_filedata(data, file_index, all_lines_counter);
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      }
    }
    (*matching_lines_counter)++;
  }
}

void print_filedata(grep_data *data, int file_index, int all_lines_counter) {
  if (data->files_count > 1 && !data->flags.h) {
    printf("%s:", data->files[file_index]);
  }
  if (data->flags.n) {
    printf("%d:", all_lines_counter);
  }
}