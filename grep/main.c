#include "file_reader.h"

int main(int argc, char *argv[]) {
  int EXIT_CODE = 0;

  grep_data data = init_data();
  int opts_counter = 1;

  char opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    parse_opt(opt, optarg, &data);
    opts_counter++;
  }

  if (data.error == SUCCESS) {
    opts_counter += (data.flags.f + data.flags.e);
    if (data.flags.e && !data.flags.f && opts_counter != argc && argc >= 3) {
      parse_filepath(argc, opts_counter, argv, &data, 0);
      data.pattern = data.opt_e_value;
    } else if (((!data.flags.e && data.flags.f) ||
                (data.flags.e && data.flags.f)) &&
               opts_counter != argc && argc >= 3) {
      parse_filepath(argc, opts_counter, argv, &data, 0);
    } else if (!data.flags.e && !data.flags.f && opts_counter != argc &&
               argc >= 3) {
      parse_filepath(argc, opts_counter, argv, &data, 1);
    } else {
      if (!data.flags.s) {
        fprintf(stderr, "s21_cat: имя файла отсутствует\n");
      }
      EXIT_CODE = 1;
    }
    if (!EXIT_CODE) {
      regex_t regex;
      regcomp(&regex, data.pattern, data.flags.i ? REG_ICASE : REG_EXTENDED);
      for (int file_index = 0; file_index < data.files_count; file_index++) {
        read_file(data.files[file_index], file_index, &data, regex);
        if (data.error == FILE_DOES_NOT_EXIST && !data.flags.s) {
          fprintf(stderr, "s21_cat: файл с таким именем отсутствует\n");
          data.error = SUCCESS;
        }
      }
      free(data.files);
      regfree(&regex);
      if (data.flags.f) {
        free(data.pattern);
      }
    }
  } else if (data.error == INVALID_FLAG_ARGUMENT) {
    fprintf(stderr, "s21_grep: флаг должен иметь аргумент\n");
    EXIT_CODE = 1;
  } else if (data.error == INVALID_FLAG) {
    fprintf(stderr, "s21_grep: неверный ключ\n");
    EXIT_CODE = 1;
  } else if (data.error == FILE_DOES_NOT_EXIST && !data.flags.s) {
    fprintf(stderr, "s21_grep: файл с таким именем отсутствует\n");
    EXIT_CODE = 1;
  } else if (data.error == INVALID_BUFFER && !data.flags.s) {
    fprintf(stderr, "s21_grep: ошибка выделения буфера\n");
    EXIT_CODE = 1;
  } else if (data.error == FAILED_READ_FILE && !data.flags.s) {
    fprintf(stderr, "s21_grep: ошибка чтения файла\n");
    EXIT_CODE = 1;
  }

  return EXIT_CODE;
}