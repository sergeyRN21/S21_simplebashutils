#include "s21_cat.h"

#define MAX_LINE_LENGTH 4096

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "eEtTsnb", long_options, 0)) != -1) {
    switch (opt) {
    case 'e':
      arg.E = 1;
      arg.v = 1;
      break;
    case 't':
      arg.T = 1;
      arg.v = 1;
      break;
    case 's':
      arg.s = 1;
      break;
    case 'n':
      arg.n = 1;
      break;
    case 'b':
      arg.b = 1;
      arg.n = 0;
      break;
    case 'E':
      arg.E = 1;
      break;
    case 'T':
      arg.T = 1;
      break;
    case '?':
      perror("ERROR");
      break;
    default:
      break;
    }
  }
  return arg;
}

int main(int argc, char *argv[]) {
  int line_count[1];
  *line_count = 1;
  arguments arg = argument_parser(argc, argv);
  output(&arg, argc, argv, line_count);
  return 0;
}

char v_output(char ch) {
  if (ch == '\n' || ch == '\t')
    return ch;
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(arguments *arg, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t')
      printf("^I");
    else {
      if (arg->E && line[i] == '\n')
        putchar('$');
      if (arg->v)
        line[i] = v_output(line[i]);
      putchar(line[i]);
    }
  }
}

void output(arguments *arg, int argc, char **argv, int *line_count) {
  for (int j = optind; j < argc; j++) {
    processFile(arg, argv[j], line_count);
  }
}

void processFile(arguments *arg, char *path, int *line_count) {
  FILE *f = fopen(path, "r");
  if (!f) {
    perror("Ошибка открытия файла");
  }

  char line[MAX_LINE_LENGTH];
  int empty_count = 0;
  while (fgets(line, sizeof(line), f)) {
    size_t line_len = strlen(line);
    if (line_len == 0) {
      empty_count++;
    } else {
      empty_count = 0;
    }
    if (arg->s && empty_count > 1) {
    } else {
      if (arg->n) {
        printf("%6d\t", *line_count);
        (*line_count)++;
      } else if (arg->b && line_len > 1) {
        printf("%6d\t", *line_count);
        (*line_count)++;
      }
      outline(arg, line, line_len);
    }
  }
  fclose(f);
}