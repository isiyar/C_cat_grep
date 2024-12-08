#include "file_reader.h"

#include "cat_flags.h"

void read_file(char *filepath, int file_index, cat_data *data) {
  FILE *file = fopen(filepath, "r");
  if (file != NULL) {
    int file_length = get_file_length(file);
    char *buffer = (char *)malloc((file_length + 1) * sizeof(char));
    if (buffer != NULL) {
      size_t bytes_read = write_buffer(buffer, file, file_length);
      if ((long)bytes_read == file_length) {
        buffer[file_length] = '\0';
        print_file_content(buffer, file_length, data, file_index);
      } else {
        data->error = FAILED_READ_FILE;
      }
    } else {
      data->error = INVALID_BUFFER;
    }
    free(buffer);
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

void print_file_content(char *buffer, int file_length, cat_data *data,
                        int file_index) {
  for (int char_index = 0; char_index < file_length; char_index++) {
    apply_flags(data, file_index, buffer, &char_index);
    printf("%c", buffer[char_index]);
  }
}