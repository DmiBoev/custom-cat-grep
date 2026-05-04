#include "my_cat.h"

int main(int argc, char **argv) {
  Flags f = {0};
  int file_index = flags_parser(&f, argc, argv);
  for (int i = file_index; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp) {
      process_input(fp, f);
      fclose(fp);
    } else {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
    }
  }
  return 0;
}

void process_input(FILE *fp, Flags f) {
  int ch;
  int line_count = 1;
  int last = '\n';
  int blank_line = 0;

  while ((ch = fgetc(fp)) != EOF) {
    // Метод De Моргана
    if (!(f.s && last == '\n' && ch == '\n' && blank_line)) {
      if (last == '\n' && ch == '\n')
        blank_line = 1;
      else
        blank_line = 0;

      if (last == '\n') {
        if (f.b && ch != '\n')
          printf("%6d\t", line_count++);
        else if (!f.b && f.n)
          printf("%6d\t", line_count++);
      }

      if (f.t && ch == '\t')
        printf("^I");
      else if (f.e && ch == '\n')
        printf("$\n");
      else if (f.v && ch != '\n' && ch != '\t') {
        if (ch >= 128) {
          printf("M-");
          ch -= 128;
        }
        if (ch < 32)
          printf("^%c", ch + 64);
        else if (ch == 127)
          printf("^?");
        else
          putchar(ch);
      } else {
        putchar(ch);
      }

      last = ch;
    }
  }
}

int flags_parser(Flags *f, int argc, char **argv) {
  int index = 1;
  while (index < argc && argv[index][0] == '-') {
    if (argv[index][1] == '-') {
      parse_long_options(f, argv[index]);
    } else {
      for (size_t j = 1; argv[index][j] != '\0'; j++) {
        set_flag(f, argv[index][j]);
      }
    }
    index++;
  }
  return index;
}

void set_flag(Flags *f, char flag) {
  if (flag == 'b')
    f->b = 1;
  else if (flag == 'e') {
    f->e = 1;
    f->v = 1;
  } else if (flag == 'E')
    f->e = 1;
  else if (flag == 'n')
    f->n = 1;
  else if (flag == 's')
    f->s = 1;
  else if (flag == 't') {
    f->t = 1;
    f->v = 1;
  } else if (flag == 'T')
    f->t = 1;
  else if (flag == 'v')
    f->v = 1;
}

int parse_long_options(Flags *f, char *option) {
  int success = 1;
  if (strcmp(option, "--number-nonblank") == 0)
    f->b = 1;
  else if (strcmp(option, "--number") == 0)
    f->n = 1;
  else if (strcmp(option, "--squeeze-blank") == 0)
    f->s = 1;
  else
    success = 0;
  return success;
}
