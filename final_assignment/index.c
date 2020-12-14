#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

void PrintError(char err[]) {
  // clang-format off
  fprintf(stderr,
          ANSI_COLOR_RED "[!] " ANSI_COLOR_YELLOW "ERROR: %s\n" ANSI_COLOR_RESET,
          err);
  // clang-format on
}

void Println(char content[]) { printf("%s\n", content); }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  char* filename = argv[1];
  Println(filename);
}