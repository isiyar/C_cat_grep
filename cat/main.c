#include "file_reader.h"

int main(int argc, char *argv[]) {
  int EXIT_CODE = 0;

  struct option long_opts[] = {{"number-nonblank", no_argument, 0, 'b'},
                               {"number", no_argument, 0, 'n'},
                               {"squeeze-blank", no_argument, 0, 's'},
                               {0, 0, 0, 0}};
  char *short_opts = "beEvnstT";

  cat_data data = {.flags = {0, 0, 0, 0, 0, 0}};
  data.error = SUCCESS;
  data.files = NULL;
  data.files_count = 0;
  data.lines_count = 1;

  int opts_counter = 1;
  char opt;

  while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
    parse_opt(opt, &data);
    opts_counter++;
  }

  if (data.error == SUCCESS) {
    if (opts_counter != argc) {
      parse_filepath(argc, opts_counter, argv, &data);
      for (int file_index = 0; file_index < data.files_count; file_index++) {
        read_file(data.files[file_index], file_index, &data);
        if (data.error == FILE_DOES_NOT_EXIST) {
          fprintf(stderr, "s21_cat: файл с таким именем отсутствует\n");
          data.error = SUCCESS;
        }
        if (data.error == INVALID_BUFFER) {
          fprintf(stderr, "s21_cat: ошибка выделения буфера\n");
          data.error = SUCCESS;
        }
        if (data.error == FAILED_READ_FILE) {
          fprintf(stderr, "s21_cat: ошибка чтения файла\n");
          data.error = SUCCESS;
        }
      }
      free(data.files);
    } else {
      fprintf(stderr, "s21_cat: имя файла отсутствует\n");
      EXIT_CODE = 1;
    }
  } else {
    fprintf(stderr, "s21_cat: неверный ключ\n");
    EXIT_CODE = 1;
  }

  return EXIT_CODE;
}