#include <stdbool.h>
#include <stdio.h>

#include "../lib/avl/avl.h"
#include "../lib/general/general.h"
#include "../lib/share/share.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    PrintError("Not enough arguments");
    return 1;
  }

  LinkedList* words = getWordsFromFile(fopen(argv[1], "r"));
  PrintInfo("File read completed");
  LinkedList* twoGramList = generate2GramList();

  printf("Query Spelling Correction - Press Ctrl-C to exit\n");
  while (true) {
    printf(">> ");
    char buffer[100];
    scanf("%s", buffer);
  }
}