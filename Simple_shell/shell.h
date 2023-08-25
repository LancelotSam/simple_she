#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _strlen(const char *str);
const char *_strtok(const char *str, const char *delim);
const char *_strchr(const char *str, int c);

#endif
