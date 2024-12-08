# Cat & Grep

## Cat

The cat utility is a standard command line in Unix-like operating systems that is used to output the contents of one or more files to standard output. It can be used to:

* Display the contents of one or more files
* Combine multiple files into a single file
* Create simple text files

### The main features of the cat utility are:

* Displaying the contents of one or more files on the screen
* Combining several files into one
* Creating simple text files using input redirection
* Numbering lines in the output
* Display non-printable characters
* Merging files by adding delimiters

### Cat options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

## Grep

The grep utility is a powerful command-line tool in Unix-like operating systems that is used to search and filter text data. It allows you to search for strings containing a particular pattern in one or more files.

### The main features of the grep utility are:

* Search for strings containing a specified pattern in one or more files
* Using regular expressions to find more complex patterns
* Output only found strings or output strings that do not contain a pattern
* Counting the number of lines found
* Display line numbers where a pattern was found
* Recursive search in directories and subdirectories
* Case ignoring during search
* Context display (lines before and after the found one)

### Grep  options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |

## Getting Started

1. Go to the directory with the desired utility

	`cd cat` or `cd grep`

2. Assemble the program

	`make`

3. Run the program

	`./s21_cat [ARGS...]` or `./s21_grep [ARGS...]`