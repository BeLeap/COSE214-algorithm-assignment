#ifndef GENERAL_H
#define GENERAL_H
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void PrintError(char[]);
void PrintInfo(char[]);
void Println(char[]);

typedef enum __BOOL {
  TRUE = 1,
  FALSE = 0,
  UNKNOWN = -1,
} BOOL;

typedef enum __COMPARE {
  BIGGER,
  SMALLER,
  EQUAL,
} COMPARE;
#endif