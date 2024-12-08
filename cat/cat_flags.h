#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

#include <ctype.h>
#include <stdio.h>

#include "parser_opts.h"

void apply_flags(cat_data *data, int file_index, char *buffer, int *char_index);
void opt_E(char *buffer, int *char_index);
void opt_s(char *buffer, int *char_index);
void opt_T(char *buffer, int *char_index);
void opt_n(char *buffer, int *char_index, int *lines_counter, int file_index);
void opt_b(char *buffer, int *char_index, int *lines_counter, int file_index);
void opt_v(char *buffer, int *char_index);

#endif