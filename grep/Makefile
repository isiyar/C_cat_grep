CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -O2
GREP_C_FILES=main.c parser_opts.c file_reader.c
GREP_OBJECT_FILES=main.o parser_opts.o file_reader.o
ALL_FILES=*.c *.h
TARGET_GREP=s21_grep


all: s21_grep clean.o

s21_grep: main.o parser_opts.o file_reader.o
	$(CC) $(CFLAGS) $(GREP_OBJECT_FILES) -o $(TARGET_GREP)

main.o: clang_edit
	$(CC) $(CFLAGS) -c main.c -o main.o

parser_opts.o: clang_edit
	$(CC) $(CFLAGS) -c parser_opts.c -o parser_opts.o

file_reader.o: clang_edit
	$(CC) $(CFLAGS) -c file_reader.c -o file_reader.o

clean.o:
	rm -f *.o

clean_grep:
	rm -f $(TARGET_GREP)

clean: clean.o clean_grep

grep_check_memory:
	valgrind --tool=memcheck --leak-check=yes -s ./$(TARGET_GREP)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

clang_edit:
	clang-format -style=Google -i $(ALL_FILES)