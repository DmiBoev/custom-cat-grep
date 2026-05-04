#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e, i, v, c, l, n, h, s, o;
} Flags;

void add_pattern(char *pattern, const char *source);
void add_pattern_from_file(const char *filename, char *pattern, Flags *f);
void process_o(regex_t *preg, const char *line, const char *filename, Flags f,
               int line_num, int mult);
void handle_print(const char *filename, Flags f, int line_num, const char *line,
                  long read, int mult, regex_t *preg);
void process_file(const char *filename, Flags f, const char *pattern, int mult);
void parse_flags(int argc, char **argv, Flags *f, char *pattern);
