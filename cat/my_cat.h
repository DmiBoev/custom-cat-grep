#include <stdio.h>
#include <string.h>

typedef struct {
  int b, e, n, s, t, v;
} Flags;

int flags_parser(Flags *f, int argc, char **argv);
void set_flag(Flags *f, char flag);
int parse_long_options(Flags *f, char *option);
void process_input(FILE *fp, Flags f);
