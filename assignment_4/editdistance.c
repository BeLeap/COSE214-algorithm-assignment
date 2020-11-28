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

// 재귀적으로 연산자 행렬을 순회하며, 두 문자열이 최소편집거리를 갖는 모든
// 가능한 정렬(alignment) 결과를 출력한다. op_matrix : 이전 상태의 연산자 정보가
// 저장된 행렬 (1차원 배열임에 주의!) col_size : op_matrix의 열의 크기 str1 :
// 문자열 1 str2 : 문자열 2 n : 문자열 1의 길이 m : 문자열 2의 길이 level :
// 재귀호출의 레벨 (0, 1, 2, ...) align_str : 정렬된 문자쌍들의 정보가 저장된
// 문자열 배열 예) "a - a", "a - b", "* - b", "ab - ba"
static void backtrace_main(int *op_matrix, int col_size, char *str1, char *str2,
                           int n, int m, int level, char align_str[][8]);

// 강의 자료의 형식대로 op_matrix를 출력 (좌하단(1,1) -> 우상단(n, m))
// 각 연산자를  괄호 안의 기호로 표시한다. 삽입(I), 삭제(D), 교체(S), 일치(M),
// 전위(T)
void print_matrix(int *op_matrix, int col_size, int n, int m);

// 두 문자열 str1과 str2의 최소편집거리를 계산한다.
// return value : 최소편집거리
// 이 함수 내부에서 print_matrix 함수와 backtrace 함수를 호출함
int min_editdistance(char *str1, char *str2);

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

////////////////////////////////////////////////////////////////////////////////
// 정렬된 문자쌍들을 출력
void print_alignment(char align_str[][8], int level) {
  int i;

  for (i = level; i >= 0; i--) {
    printf("%s\n", align_str[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////
// backtrace_main을 호출하는 wrapper 함수
// str1 : 문자열 1
// str2 : 문자열 2
// n : 문자열 1의 길이
// m : 문자열 2의 길이
void backtrace(int *op_matrix, int col_size, char *str1, char *str2, int n,
               int m) {
  char align_str[n + m][8];  // n+m strings

  // backtrace_main( op_matrix, col_size, str1, str2, n, m, 0, align_str);
}

////////////////////////////////////////////////////////////////////////////////
int main() {
  char str1[30];
  char str2[30];

  int distance;

  fprintf(stderr, "INSERT_COST = %d\n", INSERT_COST);
  fprintf(stderr, "DELETE_COST = %d\n", DELETE_COST);
  fprintf(stderr, "SUBSTITUTE_COST = %d\n", SUBSTITUTE_COST);
  fprintf(stderr, "TRANSPOSE_COST = %d\n", TRANSPOSE_COST);

  while (fscanf(stdin, "%s\t%s", str1, str2) != EOF) {
    printf("\n==============================\n");
    printf("%s vs. %s\n", str1, str2);
    printf("==============================\n");

    // distance = min_editdistance( str1, str2);

    // printf( "\nMinEdit(%s, %s) = %d\n", str1, str2, distance);
  }
  return 0;
}

typedef int BOOL;
#define TRUE 1;
#define FALSE 0;
#define UNDEF -1;

struct twoDimensionalArrayHandlers;

typedef struct twoDimensionalArray {
  int *matrix;
  int row;
  int col;

  const struct twoDimensionalArrayHandlers *handler;
} TwoDimensionalArray;

BOOL _TwoDimensionalArrayCreate(twoDimensionalArray *matrix, int row, int col) {
  matrix->matrix = (int *)malloc(sizeof(int) * row * col);

  if (matrix->matrix == NULL) {
    return FALSE;
  }

  matrix->row = row;
  matrix->col = col;
  return TRUE;
}

BOOL _TwoDimensionalArrayCheckIndex(twoDimensionalArray *matrix, int row,
                                    int col) {
  if (row > matrix->row || col > matrix->col || row < 0 || col < 0) {
    return FALSE;
  }
  return TRUE;
}

BOOL _TwoDimensionalArrayWrite(twoDimensionalArray *matrix, int row, int col,
                               int value) {
  if (!(matrix->handler->_checkIndex(matrix, row, col))) {
    return FALSE;
  }

  *((matrix->matrix) + (row * (matrix->col)) + col) = value;
  return TRUE;
}

int _TwoDimensionalArrayRead(twoDimensionalArray *matrix, int row, int col) {
  if (!(matrix->handler->_checkIndex(matrix, row, col))) {
    return FALSE;
  }

  return *((matrix->matrix) + (row * (matrix->col)) + col);
}

BOOL _TwoDimensionalArrayDestroy(twoDimensionalArray *matrix) {
  free(matrix->matrix);
  return TRUE;
}

BOOL _TwoDimensionalArrayCopy(twoDimensionalArray *fromMatrix,
                              twoDimensionalArray *toMatrix) {
  if (fromMatrix->row != toMatrix->row || fromMatrix->col != toMatrix->col) {
    return FALSE;
  }
}

typedef struct twoDimensionalArrayHandlers {
  // Allocate the appropriate amount of memory for matrix.
  BOOL(*create)
  (twoDimensionalArray *, int rowSize,
   int colSize) = _TwoDimensionalArrayCreate;

  // Check row and col
  BOOL(*_checkIndex)
  (twoDimensionalArray *, int row, int col) = _TwoDimensionalArrayCheckIndex;

  // Place the value received in the appropriate position of the matrix.
  BOOL(*write)
  (twoDimensionalArray *, int row, int col,
   int value) = _TwoDimensionalArrayWrite;

  // Read element from matrix.
  int (*read)(twoDimensionalArray *, int row,
              int col) = _TwoDimensionalArrayRead;

  // Free the matrix.
  BOOL (*destroy)(twoDimensionalArray *) = _TwoDimensionalArrayDestroy;

  // Copy matrix.
  BOOL(*copy)
  (twoDimensionalArray *fromMatrix,
   twoDimensionalArray *toMatrix) = _TwoDimensionalArrayCopy;
};

TwoDimensionalArray InitMatrix(int n, int m) {
  TwoDimensionalArray matrix;
  matrix.handler->create(&matrix, n, m);

  for (int row = 0; row < n; ++row) {
    matrix.handler->insert(&matrix, row, 0, row);
  }

  for (int col = 0; col < m; ++col) {
    matrix.handler->insert(&matrix, 0, col, col);
  }
}

int InsertCharacter(TwoDimensionalArray matrix, int row, int col) {
  return matrix.handler->read(&matrix, row - 1, col) + INSERT_COST;
}

int DeleteCharacter(TwoDimensionalArray matrix, int row, int col) {
  return matrix.handler->read(&matrix, row, col - 1) + DELETE_COST;
}

int SubstitueCharacter(TwoDimensionalArray matrix, int row, int col, char *str1,
                       char *str2) {
  if (str1[row] == str2[col]) {
    return matrix.handler->read(&matrix, row - 1, col - 1);
  }
  return matrix.handler->read(&matrix, row - 1, col - 1) + SUBSTITUTE_COST;
}

void InsertEditDistanceToMatrix(TwoDimensionalArray matrix, int row, int col,
                                char *str1, char *str2) {
  int ins = InsertCharacter(matrix, row, col);
  int del = DeleteCharacter(matrix, row, col);
  int sub = SubstitueCharacter(matrix, row, col, str1, str2);

  int min = __GetMin3(ins, del, sub);
  matrix.handler->write(&matrix, row, col, min);
}

TwoDimensionalArray BuildEditDistanceMatrix(char *str1, char *str2) {
  int n = strlen(str1);
  int m = strlen(str2);

  TwoDimensionalArray matrix;
  matrix = InitMatrix(n + 1, m + 1);

  for (int row = 1; row < matrix.row; ++row) {
    for (int col = 1; col < matrix.col; ++col) {
      if (row == col) {
        InsertEditDistanceToMatrix(matrix, row, col, str1, str2);
      }
    }
  }

  matrix.handler->destroy(&matrix);
}

int min_editdistance(char *str1, char *str2) {
  int n = strlen(str1);
  int m = strlen(str2);

  int i, j;
  int d[n + 1][m + 1];
  int op_matrix[(n + 1) * (m + 1)];

  /* TODO */

  print_matrix(op_matrix, m + 1, n, m);
  backtrace(op_matrix, m + 1, str1, str2, n, m);
}