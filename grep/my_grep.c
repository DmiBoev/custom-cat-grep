#include "my_grep.h"

int main(int argc, char **argv) {
  Flags f = {0};
  char pattern[8192] = {0};

  parse_flags(argc, argv, &f, pattern);

  if (!f.e && optind < argc) {
    add_pattern(pattern, argv[optind++]);
  }

  int mult = (argc - optind > 1);
  for (int i = optind; i < argc; i++) {
    process_file(argv[i], f, pattern, mult);
  }

  return 0;
}

void parse_flags(int argc, char **argv, Flags *f, char *pattern) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhf:so")) != -1) {
    switch (opt) {
      case 'e':
        f->e = 1;
        add_pattern(pattern, optarg);
        break;
      case 'i':
        f->i = 1;
        break;
      case 'v':
        f->v = 1;
        break;
      case 'c':
        f->c = 1;
        break;
      case 'l':
        f->l = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      case 'h':
        f->h = 1;
        break;
      case 's':
        f->s = 1;
        break;
      case 'f':
        f->e = 1;
        add_pattern_from_file(optarg, pattern, f);
        break;
      case 'o':
        f->o = 1;
        break;
    }
  }
}

void add_pattern(char *pattern, const char *source) {
  if (pattern[0] != '\0') strcat(pattern, "|");
  strcat(pattern, source);
}

void add_pattern_from_file(const char *filename, char *pattern, Flags *f) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    if (!f->s) fprintf(stderr, "s21_grep: %s: No such file\n", filename);
    return;
  }

  char *line = NULL;
  size_t len = 0;
  long read;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    add_pattern(pattern, line);
  }
  free(line);
  fclose(fp);
}

void process_file(const char *filename, Flags f, const char *pattern,
                  int mult) {
  regex_t preg;
  int cflags = REG_EXTENDED | (f.i ? REG_ICASE : 0);
  if (regcomp(&preg, pattern, cflags) != 0) return;

  FILE *fp = fopen(filename, "r");
  if (!fp) {
    if (!f.s) fprintf(stderr, "s21_grep: %s: No such file\n", filename);
    regfree(&preg);
    return;
  }

  char *line = NULL;
  size_t len = 0;
  long read;
  int matches_count = 0, line_num = 0, stop = 0;

  while (!stop && (read = getline(&line, &len, fp)) != -1) {
    line_num++;
    int success = regexec(&preg, line, 0, NULL, 0);
    int is_match = (success == 0 && !f.v) || (success != 0 && f.v);

    if (is_match) {
      matches_count++;
      handle_print(filename, f, line_num, line, read, mult, &preg);
      if (f.l) stop = 1;
    }
  }

  if (f.c && !f.l) {
    if (mult && !f.h) printf("%s:", filename);
    printf("%d\n", matches_count);
  }
  if (f.l && matches_count > 0) printf("%s\n", filename);

  free(line);
  fclose(fp);
  regfree(&preg);
}

void process_o(regex_t *preg, const char *line, const char *filename, Flags f,
               int line_num, int mult) {
  regmatch_t pmatch;
  const char *ptr = line;
  while (regexec(preg, ptr, 1, &pmatch, 0) == 0) {
    if (mult && !f.h) printf("%s:", filename);
    if (f.n) printf("%d:", line_num);
    printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so), ptr + pmatch.rm_so);
    ptr += pmatch.rm_eo;
    if (pmatch.rm_so == pmatch.rm_eo) ptr++;
  }
}

void handle_print(const char *filename, Flags f, int line_num, const char *line,
                  long read, int mult, regex_t *preg) {
  if (f.c || f.l) return;
  if (f.o && !f.v) {
    process_o(preg, line, filename, f, line_num, mult);
  } else {
    if (mult && !f.h) printf("%s:", filename);
    if (f.n) printf("%d:", line_num);
    printf("%s", line);
    if (read > 0 && line[read - 1] != '\n') printf("\n");
  }
}
