#include <assert.h>  // assert
#include <stdio.h>
#include <stdlib.h>  // atoi, rand, qsort, malloc
#include <time.h>    //time

#define RANGE 10000

typedef struct {
  int x;
  int y;
} t_point;

typedef struct {
  t_point from;
  t_point to;
} t_line;

////////////////////////////////////////////////////////////////////////////////
// function declaration
// 점들의 집합(points; 점의 수 num_point)에서 점 p1과 점 pn을 잇는 직선의 upper
// hull을 구하는 함수 (재귀호출) [output] lines: convex hull을 이루는 선들의
// 집합 [output] num_line: 선의 수 [output] capacity: lines에 할당된 메모리의
// 용량 (할당 가능한 선의 수) return value: 선들의 집합(lines)에 대한 포인터
t_line* upper_hull(t_point* points, int num_point, t_point p1, t_point pn,
                   t_line* lines, int* num_line, int* capacity);

// 직선(ax+by-c=0)과 주어진 점 p(x1, y1) 간의 거리
// distance = |ax1+by1-c| / sqrt(a^2 + b^2)
// 실제로는 sqrt는 계산하지 않음
// return value: 직선과 점 사이의 거리 (분모 제외)
float distance(float a, float b, float c, t_point p);

// 두 점(from, to)을 연결하는 직선(ax + by - c = 0)으로 n개의 점들의 집합 s(점의
// 수 num_point)를 s1(점의 수 n1)과 s2(점의 수 n2)로 분리하는 함수 [output] s1 :
// 직선의 upper(left)에 속한 점들의 집합 (ax+by-c < 0) [output] s2 :
// lower(right)에 속한 점들의 집합 (ax+by-c > 0) [output] n1 : s1 집합에 속한
// 점의 수 [output] n2 : s2 집합에 속한 점의 수
void separate_points(t_point* points, int num_point, t_point from, t_point to,
                     t_point* s1, t_point* s2, int* n1, int* n2);

////////////////////////////////////////////////////////////////////////////////
void print_header(char* filename) {
  printf("#! /usr/bin/env Rscript\n");
  printf("png(\"%s\", width=700, height=700)\n", filename);

  printf("plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}

////////////////////////////////////////////////////////////////////////////////
void print_footer(void) { printf("dev.off()\n"); }

////////////////////////////////////////////////////////////////////////////////
// qsort를 위한 비교 함수
int cmp_x(const void* p1, const void* p2) {
  t_point* p = (t_point*)p1;
  t_point* q = (t_point*)p2;

  float diff = p->x - q->x;

  return ((diff >= 0.0) ? ((diff > 0.0) ? +1 : 0) : -1);
}

////////////////////////////////////////////////////////////////////////////////
void print_points(t_point* points, int num_point) {
  int i;
  printf("\n#points\n");

  for (i = 0; i < num_point; i++)
    printf("points(%d,%d)\n", points[i].x, points[i].y);
}

////////////////////////////////////////////////////////////////////////////////
void print_line_segments(t_line* lines, int num_line) {
  int i;

  printf("\n#line segments\n");

  for (i = 0; i < num_line; i++)
    printf("segments(%d,%d,%d,%d)\n", lines[i].from.x, lines[i].from.y,
           lines[i].to.x, lines[i].to.y);
}

////////////////////////////////////////////////////////////////////////////////
// [input] points : set of points
// [input] num_point : number of points
// [output] num_line : number of lines
// return value : pointer of set of line segments that forms the convex hull
t_line* convex_hull(t_point* points, int num_point, int* num_line) {
  int capacity = 10;

  t_line* lines = (t_line*)malloc(capacity * sizeof(t_line));
  *num_line = 0;

  // s1: set of points
  t_point* s1 = (t_point*)malloc(sizeof(t_point) * num_point);
  assert(s1 != NULL);

  // s2: set of points
  t_point* s2 = (t_point*)malloc(sizeof(t_point) * num_point);
  assert(s2 != NULL);

  int n1, n2;  // number of points in s1, s2, respectively

  // x 좌표에 따라 정렬된 점들의 집합이 입력된 경우
  // points[0] : leftmost point (p1)
  // points[num_point-1] : rightmost point (pn)

  // 점들을 분리
  separate_points(points, num_point, points[0], points[num_point - 1], s1, s2,
                  &n1, &n2);

  // upper hull을 구한다.
  lines = upper_hull(s1, n1, points[0], points[num_point - 1], lines, num_line,
                     &capacity);
  lines = upper_hull(s2, n2, points[num_point - 1], points[0], lines, num_line,
                     &capacity);

  free(s1);
  free(s2);

  return lines;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
  float x, y;
  int num_point;  // number of points

  if (argc != 2) {
    printf("%s number_of_points\n", argv[0]);
    return 0;
  }

  num_point = atoi(argv[1]);
  if (num_point <= 0) {
    printf("The number of points should be a positive integer!\n");
    return 0;
  }

  t_point* points;
  points = (t_point*)malloc(sizeof(t_point) * num_point);
  assert(points != NULL);

  // making points
  srand(time(NULL));
  for (int i = 0; i < num_point; i++) {
    x = rand() % RANGE + 1;  // 1 ~ RANGE random number
    y = rand() % RANGE + 1;

    points[i].x = x;
    points[i].y = y;
  }

  fprintf(stderr, "%d points created!\n", num_point);

  // sort the points by their x coordinate
  qsort(points, num_point, sizeof(t_point), cmp_x);

  print_header("convex.png");

  print_points(points, num_point);

  // convex hull algorithm
  int num_line;
  t_line* lines = convex_hull(points, num_point, &num_line);

  fprintf(stderr, "%d lines created!\n", num_line);

  print_line_segments(lines, num_line);

  print_footer();

  free(points);
  free(lines);

  return 0;
}

typedef struct lineEquation {
  int a, b, c;
} LineEquation;

LineEquation generateLineFromTwoPoints(t_point from, t_point to) {
  LineEquation line;
  line.a = to.y - from.y;
  line.b = from.x - to.x;
  line.c = (from.x * to.y) - (from.y * to.x);
  return line;
}

t_point findFarthestPoint(LineEquation line, t_point* points, int num_points) {
  t_point farthestPoint;
  float maxDistance = -1;
  for (int i = 0; i < num_points; ++i) {
    float dist = distance(line.a, line.b, line.c, *(points + i));

    if (dist > maxDistance) {
      maxDistance = dist;
      farthestPoint = *(points + i);
    }
  }

  return farthestPoint;
}

t_line* upper_hull(t_point* points, int num_point, t_point p1, t_point pn,
                   t_line* lines, int* num_line, int* capacity) {
  if (num_point == 0) {
    t_line line;
    line.from = p1;
    line.to = pn;

    (*num_line)++;
    if (*num_line > *capacity) {
      *capacity *= 2;
      lines = (t_line*)realloc(lines, sizeof(t_line) * *capacity);
      fprintf(stderr, "realloc(%d)\n", *capacity);
    }
    *(lines + *num_line - 1) = line;

    return lines;
  }

  LineEquation extreamLine = generateLineFromTwoPoints(p1, pn);
  t_point farthestPoint = findFarthestPoint(extreamLine, points, num_point);

  LineEquation leftLine = generateLineFromTwoPoints(p1, farthestPoint);

  int n1 = 0;
  int n2 = 0;
  t_point* s1 = (t_point*)malloc(sizeof(t_point) * num_point);
  t_point* s2 = (t_point*)malloc(sizeof(t_point) * num_point);

  separate_points(points, num_point, p1, farthestPoint, s1, s2, &n1, &n2);

  lines = upper_hull(s1, n1, p1, farthestPoint, lines, num_line, capacity);

  LineEquation rightLine = generateLineFromTwoPoints(farthestPoint, pn);
  separate_points(points, num_point, farthestPoint, pn, s1, s2, &n1, &n2);

  lines = upper_hull(s1, n1, farthestPoint, pn, lines, num_line, capacity);

  free(s1);
  free(s2);

  return lines;
}

float distance(float a, float b, float c, t_point p) {
  int x = p.x;
  int y = p.y;

  float mother = a * x + b * y - c;
  if (mother < 0) {
    mother = -mother;
  }
  float son = a * a + b * b;

  return mother / son;
}

#define TRUE 1
#define FALSE 0
#define UNDEF -1
typedef int BOOL;

BOOL isUpper(LineEquation line, t_point point) {
  int result = line.a * point.x + line.b * point.y - line.c;

  if (result > 0) {
    return TRUE;
  } else if (result < 0) {
    return FALSE;
  } else {
    return UNDEF;
  }
}

void separate_points(t_point* points, int num_point, t_point from, t_point to,
                     t_point* s1, t_point* s2, int* n1, int* n2) {
  LineEquation line = generateLineFromTwoPoints(from, to);
  *n1 = 0;
  *n2 = 0;

  for (int i = 0; i < num_point; ++i) {
    BOOL isUp = isUpper(line, *(points + i));

    if (isUp == TRUE) {
      (*n1)++;
      *(s1 + (*n1) - 1) = *(points + i);
    } else if (isUp == FALSE) {
      (*n2)++;
      *(s2 + (*n2) - 1) = *(points + i);
    }
  }
}