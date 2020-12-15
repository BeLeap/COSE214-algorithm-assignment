#include "print.h"

void PrintError(char err[]) {
  // clang-format off
  fprintf(stderr,
          ANSI_COLOR_RED "[!] " ANSI_COLOR_YELLOW "ERROR: %s\n" ANSI_COLOR_RESET,
          err);
  // clang-format on
}

void Println(char content[]) { printf("%s\n", content); }