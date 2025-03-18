#include "s21_grep.h"

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
    case 'e':
      arg.e = 1;
      pattern_add(&arg, optarg);
      break;
    case 'i':
      arg.i = REG_ICASE;
      break;
    case 'v':
      arg.v = 1;
      break;
    case 'c':
      arg.c = 1;
      break;
    case 'l':
      arg.c = 1;
      arg.l = 1;
      break;
    case 'n':
      arg.n = 1;
      break;
    case 'h':
      arg.h = 1;
      break;
    case 's':
      arg.s = 1;
      break;
    case 'f':
      arg.f = 1;
      add_reg_from_file(&arg, optarg);
      break;
    case 'o':
      arg.o = 1;
      break;
    case '?':
      perror("ERROR");
      break;
    default:
      break;
    }
  }

  if (arg.len_pattern == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

int main(int argc, char **argv) {
  arguments arg = argument_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}

void pattern_add(arguments *arg, char *pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(arguments *arg, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s)
      perror(filepath);
  }

  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), f)) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    pattern_add(arg, line);
  }
  fclose(f);
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n')
    putchar('\n');
}

void print_match(regex_t *re, char *line) {
  regmatch_t match;
  int offset = 0;
  int result = 1;
  while (result != 0) {
    result = regexec(re, line + offset, 1, &match, 0);

    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(arguments arg, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s)
      perror(path);
  }
  char line[MAX_LINE_LENGTH];
  int line_count = 1;
  int search_count = 0;

  while (fgets(line, sizeof(line), f) != NULL) {
    int result = regexec(reg, line, 0, NULL, 0);

    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h)
          printf("%s:", path);
        if (arg.n)
          printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line, strlen(line));
        }
      }
      search_count++;
    }
    line_count++;
  }
  if (arg.c && !arg.l) {
    if (!arg.h)
      printf("%s:", path);
    printf("%d\n", search_count);
  }
  if (arg.l && search_count > 0)
    printf("%s\n", path);

  fclose(f);
}

void output(arguments arg, int argc, char **argv) {
  regex_t re;

  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error)
    perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}