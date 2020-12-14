#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

///////////////////
/* Library Start */
///////////////////
void PrintError(char err[]) {
  // clang-format off
  fprintf(stderr,
          ANSI_COLOR_RED "[!] " ANSI_COLOR_YELLOW "ERROR: %s\n" ANSI_COLOR_RESET,
          err);
  // clang-format on
}

void Println(char content[]) { printf("%s\n", content); }
/////////////////
/* Library End */
/////////////////

// Word List
typedef struct __Word {
  char* word;
  struct __Word* next;
} Word;

// Index List
typedef struct __Index {
  char id[3];
  Word* head;
  struct __Index* next;
} Index;

// Create and Initialize Index
Index CreateIndex() {
  Index root;
  memcpy(root.id, "\0\0\0", sizeof(root.id));
  root.head = NULL;
  root.next = NULL;
}

// Append new word list
void AppendIndex(Index* root, char id[3], Word* wordRoot) {
  Index* curr = root;
  while (curr->next != NULL) {
    curr = curr->next;
  }

  Index* newIndex = (Index*)malloc(sizeof(Index));
  strcpy(newIndex->id, id);
  newIndex->head = wordRoot;
  newIndex->next = NULL;

  curr->next = newIndex;

  return;
}

void DestroyWordList(Word* root) {
  if (root == NULL) {
    return;
  }

  free(root->word);
  DestroyWordList(root->next);

  return;
}

void DestroyAll(Index* root) {
  if (root == NULL) {
    return;
  }

  DestroyWordList(root->head);
  DestroyAll(root->next);
  return;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  char* filename = argv[1];

  Index root = CreateIndex();

  return 0;
}