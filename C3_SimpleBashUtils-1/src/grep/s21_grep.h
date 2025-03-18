#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 10000

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} arguments;

void pattern_add(arguments *arg, char *pattern);
void add_reg_from_file(arguments *arg, char *filepath);
void output_line(char *line, int n);
void print_match(regex_t *re, char *line);
void processFile(arguments arg, char *path, regex_t *reg);
void output(arguments arg, int argc, char **argv);

#endif
