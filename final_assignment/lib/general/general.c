#include "general.h"

void PrintError(char err[]) {
  // clang-format off
  fprintf(stderr,
          ANSI_COLOR_YELLOW "[!] " ANSI_COLOR_RED "ERROR: %s\n" ANSI_COLOR_RESET,
          err);
  // clang-format on
}

void PrintInfo(char info[]) {
  // clang-format off
  fprintf(stdout,
          ANSI_COLOR_YELLOW "[!] " ANSI_COLOR_GREEN "INFO: %s\n" ANSI_COLOR_RESET,
          info
  );
  // clang-format on
}

void Println(char content[]) { printf("%s\n", content); }