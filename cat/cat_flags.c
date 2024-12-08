#include "cat_flags.h"

void apply_flags(cat_data *data, int file_index, char *buffer,
                 int *char_index) {
  if (data->flags.b || data->flags.n) {
    if (data->flags.b) {
      opt_b(buffer, char_index, &data->lines_count, file_index);
    } else {
      opt_n(buffer, char_index, &data->lines_count, file_index);
    }
  }
  if (data->flags.E) {
    opt_E(buffer, char_index);
  }
  if (data->flags.s) {
    opt_s(buffer, char_index);
  }
  if (data->flags.T) {
    opt_T(buffer, char_index);
  }
  if (data->flags.v) {
    opt_v(buffer, char_index);
  }
}

void opt_E(char *buffer, int *char_index) {
  if (buffer[*char_index] == '\n') {
    printf("$");
  }
}

void opt_s(char *buffer, int *char_index) {
  if (*char_index > 0 && buffer[*char_index - 1] == '\n' &&
      buffer[*char_index] == '\n' && buffer[*char_index + 1] == '\n') {
    while (buffer[*char_index] == '\n') {
      (*char_index)++;
    }
    (*char_index)--;
  }
}

void opt_T(char *buffer, int *char_index) {
  if (buffer[*char_index] == '\t') {
    printf("^");
    buffer[*char_index] = 'I';
  }
}

void opt_n(char *buffer, int *char_index, int *lines_counter, int file_index) {
  if ((file_index == 0 && *char_index == 0) ||
      (*char_index > 0 && buffer[*char_index - 1] == '\n')) {
    printf("%6d\t", (*lines_counter)++);
  }
}

void opt_b(char *buffer, int *char_index, int *lines_counter, int file_index) {
  if (((file_index == 0 && *char_index == 0) ||
       (*char_index > 0 && buffer[*char_index - 1] == '\n')) &&
      buffer[*char_index] != '\n') {
    printf("%6d\t", (*lines_counter)++);
  }
}

void opt_v(char *buffer, int *char_index) {
  unsigned char c = (unsigned char)buffer[*char_index];
  if (c != '\t' && c != '\n') {
    if (c < 32) {
      buffer[*char_index] = c + 64;
      printf("^");
    } else if (c == 127) {
      buffer[*char_index] = '?';
      printf("^");
    } else if (c > 127) {
      if (c < 160) {
        buffer[*char_index] = c - 64;
        printf("M-^");
      } else {
        buffer[*char_index] = c & 127;
        printf("M-");
      }
    }
  }
}