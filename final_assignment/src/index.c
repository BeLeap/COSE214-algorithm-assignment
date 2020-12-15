#include <stdio.h>

#include "../lib/print/print.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  return 0;
}