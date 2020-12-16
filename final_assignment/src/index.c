#include <stdio.h>

#include "../lib/general/general.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  return 0;
}