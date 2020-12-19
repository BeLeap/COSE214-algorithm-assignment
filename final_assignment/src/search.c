#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT_OP 0x01
#define DELETE_OP 0x02
#define SUBSTITUTE_OP 0x04
#define MATCH_OP 0x08
#define TRANSPOSE_OP 0x10

#define INSERT_COST 1
#define DELETE_COST 1
#define SUBSTITUTE_COST 1
#define TRANSPOSE_COST 1

#define INT_MAX 2147483646

#include "../lib/general/general.h"
#include "../lib/linkedlist/linkedlist.h"

int CheckFrequency(char*);

int main(int argc, char* argv[]) {  // indexFile
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  FILE* wordIdFile = fopen("word_id.txt", "r");

  printf("Query Spelling Correction - Press Ctrl-C to exit");
  while (true) {
    printf(">> ");
    char input[100];
    scanf("%s", input);

    for (int i = 0; i < strlen(input) - 1; ++i) {
      char indexFileName[100];
      sprintf(indexFileName, "%s/%c%c.txt", argv[1], input[i], input[i + 1]);
      FILE* indexFile = fopen(indexFileName, "rb");
      if (indexFile == NULL) {
        PrintError("Failed to open file");
        return 1;
      }

      while (true) {
        if (feof(indexFile)) {
          break;
        }

        int wordId = 0;
        fread(&wordId, sizeof(int), 1, indexFile);
      }
      fclose(indexFile);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// 세 정수 중에서 가장 작은 값을 리턴한다.
static int __GetMin3(int a, int b, int c) {
  int min = a;
  if (b < min) min = b;
  if (c < min) min = c;
  return min;
}

////////////////////////////////////////////////////////////////////////////////
// 네 정수 중에서 가장 작은 값을 리턴한다.
static int __GetMin4(int a, int b, int c, int d) {
  int min = __GetMin3(a, b, c);
  return (min > d) ? d : min;
}

int min_editdistance(char* str1, char* str2) {
  int n = strlen(str1);
  int m = strlen(str2);

  int d[n + 1][m + 1];
  int op_matrix[(n + 1) * (m + 1)];

  // Zero-fill
  for (int col = 0; col < m + 1; ++col) {
    for (int row = 0; row < n + 1; ++row) {
      d[row][col] = 0;
      op_matrix[(row * (m + 1)) + col] = 0;
    }
  }

  // Initialize Matrix
  for (int col = 0; col < m + 1; ++col) {
    d[0][col] = col * INSERT_COST;
    op_matrix[col] |= INSERT_OP;
  }

  for (int row = 0; row < n + 1; ++row) {
    d[row][0] = row * DELETE_COST;
    op_matrix[(row * (m + 1))] |= DELETE_OP;
  }
  op_matrix[0] = 0;

  // Build Distance Matrix
  for (int col = 1; col < m + 1; ++col) {
    for (int row = 1; row < n + 1; ++row) {
      int ins = d[row][col - 1] + INSERT_COST;
      int del = d[row - 1][col] + DELETE_COST;
      int sub = d[row - 1][col - 1] +
                (str1[row - 1] == str2[col - 1] ? 0 : SUBSTITUTE_COST);
      int tra = (row > 1 && col > 1 && (str1[row - 1] == str2[col - 2]) &&
                 (str1[row - 2] == str2[col - 1]))
                    ? d[row - 2][col - 2] + TRANSPOSE_COST
                    : INT_MAX;

      int min = __GetMin4(ins, del, sub, tra);

      if (ins == min) {
        op_matrix[(row * (m + 1)) + col] |= INSERT_OP;
      }

      if (del == min) {
        op_matrix[(row * (m + 1)) + col] |= DELETE_OP;
      }

      if (sub == min) {
        if (str1[row - 1] != str2[col - 1])
          op_matrix[(row * (m + 1)) + col] |= SUBSTITUTE_OP;
      }

      if (tra == min) {
        op_matrix[(row * (m + 1)) + col] |= TRANSPOSE_OP;
      }
      d[row][col] = min;
    }
  }

  return d[m][n];
}
