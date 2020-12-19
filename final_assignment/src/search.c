#include <stdbool.h>
#include <stdio.h>

#include "../lib/general/general.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    PrintError("Not enough arguments");
    return 1;
  }
}