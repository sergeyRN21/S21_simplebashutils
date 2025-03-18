#ifndef S21CAT_H
#define S21CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int b, n, s, E, T, v;
} arguments;

char v_output(char ch);
void t_output(arguments *arg, char *line, int n);
void outline(arguments *arg, char *line, int n);
void output(arguments *arg, int argc, char **argv, int *line_count);
void processFile(arguments *arg, char *path, int *line_count);

#endif