# Simple Bash Utils 🛠️

A custom implementation of the standard Bash utilities `cat` and `grep`, written in C. This project focuses on text processing, file I/O, and command-line argument parsing.

---

### 📋 Overview

This repository contains two main utilities:
1. **my_cat**: A utility that reads files sequentially, writing them to standard output. Supports formatting options like line numbering and non-printable character display.
2. **my_grep**: A powerful pattern matching utility. It searches for patterns in files using POSIX regular expressions.

---

### 🛠 Tech Stack
*   **Language:** C (C11)
*   **Libraries:** `regex.h`, `stdio.h`, `stdlib.h`, `getopt.h`, `string.h`
*   **Tools:** GCC, Make

---

### ✨ Key Features

#### my_cat
Supports standard flags:
* `-b` (`--number-nonblank`): Numbers only non-empty lines.
* `-e` / `-E`: Displays `$` at the end of each line.
* `-n` (`--number`): Numbers all output lines.
* `-s` (`--squeeze-blank`): Squeezes multiple adjacent empty lines into one.
* `-t` / `-T`: Displays TAB characters as `^I`.

#### my_grep
Supports complex searching with POSIX regex:
* `-e`: Pattern matching (multiple patterns supported).
* `-i`: Case-insensitive search.
* `-v`: Inverts match (selects non-matching lines).
* `-c`: Displays only the count of matching lines.
* `-l`: Displays only names of files with matches.
* `-n`: Numbers matching lines.
* `-h`: Suppresses prefixing filenames on output.
* `-f`: Takes patterns from a file.
* `-o`: Prints only the matched parts of a line.

---

### 🚀 Build & Usage

#### Compilation
Use `Makefile` to compile the utilities:
```bash
# To build both utilities
make all

# To build specifically cat or grep
make my_cat
make my_grep
```

#### Usage Examples
```bash
# cat example: number all lines in a file
./my_cat -n test.txt

# grep example: search for a pattern in multiple files (case-insensitive)
./my_grep -i "error" log_file.txt system.log

# grep example: using multiple patterns
./my_grep -e "pattern1" -e "pattern2" data.txt
```

---

### 📁 Implementation Details
*   **Regex Engine:** Used `regex.h` for robust pattern matching in `grep`.
*   **Buffer Management:** Implemented dynamic memory allocation for handling long lines using `getline`.
*   **Flag Parsing:** Custom logic for long options (e.g., `--number`) and combined short flags (e.g., `-be`).

---
*Developed by [Dmitry Boev](https://github.com)*
