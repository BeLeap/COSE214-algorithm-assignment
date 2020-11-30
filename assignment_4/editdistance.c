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
#define SUBSTITUTE_COST 2
#define TRANSPOSE_COST 2

int count = 0;

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

  memset(align_str, 0, sizeof(align_str));
  count = 0;
  backtrace_main(op_matrix, col_size, str1, str2, n, m, 0, align_str);
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

    distance = min_editdistance(str1, str2);

    printf("\nMinEdit(%s, %s) = %d\n", str1, str2, distance);
  }
  return 0;
}

#define DEBUG 0

typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

int min_editdistance(char *str1, char *str2) {
  int n = strlen(str1);
  int m = strlen(str2);

  int i, j;

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
    d[0][col] = col;
    op_matrix[col] |= INSERT_OP;
  }

  for (int row = 0; row < n + 1; ++row) {
    d[row][0] = row;
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

      int min = __GetMin3(ins, del, sub);

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
      d[row][col] = min;
    }
  }

#if DEBUG
  for (int col = 0; col < m + 1; ++col) {
    for (int row = 0; row < n + 1; ++row) {
      printf("%d ", d[row][col]);
    }
    printf("\n");
  }
#endif

  print_matrix(op_matrix, m + 1, n, m);
  backtrace(op_matrix, m + 1, str1, str2, n, m);

  return d[m][n];
}

void print_matrix(int *op_matrix, int col_size, int n, int m) {
  for (int col = m; col > 0; --col) {
    for (int row = 1; row <= n; ++row) {
      int op = op_matrix[row * col_size + col];
      int count = 0;
      if ((op & SUBSTITUTE_OP) != 0) {
        printf("S");
        count++;
      }
      if ((op & INSERT_OP) != 0) {
        printf("I");
        count++;
      }
      if ((op & DELETE_OP) != 0) {
        printf("D");
        count++;
      }

      if (op == 0) {
        printf("M");
        count++;
      }

      for (int cnt = count; cnt < 5; ++cnt) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

static void backtrace_main(int *op_matrix, int col_size, char *str1, char *str2,
                           int n, int m, int level, char align_str[][8]) {
  if (n <= 0 || m <= 0) {
    fflush(stdout);
    printf("\n[%d]===========================\n", ++count);
    print_alignment(align_str, level);
    return;
  }

  int op = op_matrix[n * col_size + m];

  if ((op & SUBSTITUTE_OP) != 0 || op == 0) {
    align_str[level][0] = str1[n - 1];
    align_str[level][1] = ' ';
    align_str[level][2] = '-';
    align_str[level][3] = ' ';
    align_str[level][4] = str2[m - 1];
    align_str[level][5] = '\0';
    align_str[level][6] = '\0';
    align_str[level][7] = '\0';
#if DEBUG
    printf("%d: %s\n", level, align_str[level]);
#endif
    backtrace_main(op_matrix, col_size, str1, str2, n - 1, m - 1, level + 1,
                   align_str);
  }

  if ((op & INSERT_OP) != 0) {
    align_str[level][0] = '*';
    align_str[level][1] = ' ';
    align_str[level][2] = '-';
    align_str[level][3] = ' ';
    align_str[level][4] = str2[m - 1];
    align_str[level][5] = '\0';
    align_str[level][6] = '\0';
    align_str[level][7] = '\0';
#if DEBUG
    printf("%d: %s\n", level, align_str[level]);
#endif
    backtrace_main(op_matrix, col_size, str1, str2, n, m - 1, level + 1,
                   align_str);
  }

  if ((op & DELETE_OP) != 0) {
    align_str[level][0] = str1[n - 1];
    align_str[level][1] = ' ';
    align_str[level][2] = '-';
    align_str[level][3] = ' ';
    align_str[level][4] = '*';
    align_str[level][5] = '\0';
    align_str[level][6] = '\0';
    align_str[level][7] = '\0';
#if DEBUG
    printf("%d: %s\n", level, align_str[level]);
#endif
    backtrace_main(op_matrix, col_size, str1, str2, n - 1, m, level + 1,
                   align_str);
  }
}