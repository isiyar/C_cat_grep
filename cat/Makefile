CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -O2
CAT_C_FILES=main.c parser_opts.c file_reader.c cat_flags.c
CAT_OBJECT_FILES=main.o parser_opts.o file_reader.o cat_flags.o
ALL_FILES=*.c *.h
TARGET_CAT=s21_cat


all: s21_cat clean.o

s21_cat: main.o parser_opts.o file_reader.o cat_flags.o
	$(CC) $(CFLAGS) $(CAT_OBJECT_FILES) -o $(TARGET_CAT)

main.o: clang_edit
	$(CC) $(CFLAGS) -c main.c -o main.o

parser_opts.o: clang_edit
	$(CC) $(CFLAGS) -c parser_opts.c -o parser_opts.o

file_reader.o: clang_edit
	$(CC) $(CFLAGS) -c file_reader.c -o file_reader.o

cat_flags.o: clang_edit
	$(CC) $(CFLAGS) -c cat_flags.c -o cat_flags.o

clean.o:
	rm -f *.o

clean_cat:
	rm -f $(TARGET_CAT)

clean: clean.o clean_cat

cat_check_memory:
	valgrind --tool=memcheck --leak-check=yes -s ./$(TARGET_CAT)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

clang_edit:
	clang-format -style=Google -i $(ALL_FILES)