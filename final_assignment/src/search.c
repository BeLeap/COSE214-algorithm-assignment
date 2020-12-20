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

int CheckFrequency(char*);
void FindWord(FILE*, int, char[]);
int min_editdistance(char* str1, char* str2);

int freqList[5000000];
char wordList[5000000][100];

int main(void) {  // indexFile
  FILE* wordIdFile = fopen("word_id.txt", "r");
  int* distanceList = (int*)malloc(sizeof(int) * 5000000);

  while (true) {
    if (feof(wordIdFile)) {
      break;
    }

    char buff[100];
    int id;
    fscanf(wordIdFile, "%s %d", buff, &id);
    strcpy(wordList[id], buff);
  }

  printf("Query Spelling Correction - Press Ctrl-C to exit\n");
  while (true) {
    for (int i = 0; i < 5000000; ++i) {
      freqList[i] = 0;
      distanceList[i] = -1;
    }
    printf(">> ");
    char input[100];
    scanf("%s", input);

    for (int i = 0; i < strlen(input) - 1; ++i) {
      char indexFileName[100];
      sprintf(indexFileName, "%c%c.index", input[i], input[i + 1]);
      FILE* indexFile = fopen(indexFileName, "rb");
      if (indexFile == NULL) {
        fprintf(stderr, "Failed to open file");
        return 1;
      }

      while (true) {
        int wordId = 0;
        if (fread(&wordId, sizeof(int), 1, indexFile) == 1) {
          if (wordId == 0) continue;
          freqList[wordId]++;
        } else {
          break;
        }
      }
      fclose(indexFile);
    }

    int count = 0;
    int prev_freq = 0;
    while (count < 10) {
      int freq = -1;
      int wordId = 0;
      for (int i = 0; i < 5000000; ++i) {
        if (freq < freqList[i] && freqList[i] != -1) {
          freq = freqList[i];
          wordId = i;
        }
      }
      freqList[wordId] = -1;
      if (wordId == 0) break;

      int distance = min_editdistance(input, wordList[wordId]);
      distanceList[wordId] = distance;

      if (prev_freq != freq && prev_freq != 0) {
        while (count < 10) {
          int minDistanceWordId = 0;
          int min = INT_MAX;
          for (int i = 0; i < 5000000; ++i) {
            if (distanceList[i] < min && distanceList[i] != -1) {
              minDistanceWordId = i;
              min = distanceList[i];
            }
          }
          distanceList[minDistanceWordId] = -1;
          if (minDistanceWordId == 0) break;
          printf("%s, %lf\n", wordList[minDistanceWordId],
                 1 - ((float)min / strlen(input)));
          count++;
        }
      }
      prev_freq = freq;
    }
    while (count < 10) {
      int minDistanceWordId = 0;
      int min = INT_MAX;
      for (int i = 0; i < 5000000; ++i) {
        if (distanceList[i] < min && distanceList[i] != -1) {
          minDistanceWordId = i;
          min = distanceList[i];
        }
      }
      distanceList[minDistanceWordId] = -1;
      printf("%s, %lf\n", wordList[minDistanceWordId],
             1 - ((float)min / strlen(input)));
      count++;
    }
  }

  fclose(wordIdFile);
}

void FindWord(FILE* wordIdFile, int wordId, char buffer[]) {
  if (wordIdFile == NULL) {
    return;
  }

  while (true) {
    if (feof(wordIdFile)) {
      rewind(wordIdFile);
      return;
    }

    char buff[100];
    int id;
    fscanf(wordIdFile, "%s %d", buff, &id);

    if (wordId == id) {
      strcpy(buffer, buff);
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

  return d[n][m];
}
