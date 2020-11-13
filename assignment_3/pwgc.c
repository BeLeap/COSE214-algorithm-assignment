#include <stdio.h>
#include <stdlib.h>

#define PEASANT 0x08
#define WOLF 0x04
#define GOAT 0x02
#define CABBAGE 0x01

// 주어진 상태 state의 이름(마지막 4비트)을 화면에 출력
// 예) state가 7(0111)일 때, "<0111>"을 출력
static void print_statename(FILE *fp, int state);

// 주어진 상태 state에서 농부, 늑대, 염소, 양배추의 상태를 각각 추출하여 p, w,
// g, c에 저장 예) state가 7(0111)일 때, p = 0, w = 1, g = 1, c = 1
static void get_pwgc(int state, int *p, int *w, int *g, int *c);

// 허용되지 않는 상태인지 검사
// 예) 농부없이 늑대와 염소가 같이 있는 경우 / 농부없이 염소와 양배추가 같이
// 있는 경우 return value: 1 허용되지 않는 상태인 경우, 0 허용되는 상태인 경우
static int is_dead_end(int state);

// state1 상태에서 state2 상태로의 전이 가능성 점검
// 농부 또는 농부와 다른 하나의 아이템이 강 반대편으로 이동할 수 있는 상태만
// 허용 허용되지 않는 상태(dead-end)로의 전이인지 검사 return value: 1 전이
// 가능한 경우, 0 전이 불이가능한 경우
static int is_possible_transition(int state1, int state2);

// 상태 변경: 농부 이동
// return value : 새로운 상태
static int changeP(int state);

// 상태 변경: 농부, 늑대 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePW(int state);

// 상태 변경: 농부, 염소 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePG(int state);

// 상태 변경: 농부, 양배추 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePC(int state);

// 주어진 state가 이미 방문한 상태인지 검사
// return value : 1 visited, 0 not visited
static int is_visited(int visited[], int level, int state);

// 방문한 상태들을 차례로 화면에 출력
static void print_states(int visited[], int count);

// recursive function
static void dfs_main(int state, int goal_state, int level, int visited[]);

////////////////////////////////////////////////////////////////////////////////
// 상태들의 인접 행렬을 구하여 graph에 저장
// 상태간 전이 가능성 점검
// 허용되지 않는 상태인지 점검
void make_adjacency_matrix(int graph[][16]);

// 인접행렬로 표현된 graph를 화면에 출력
void print_graph(int graph[][16], int num);

// 주어진 그래프(graph)를 .net 파일로 저장
// pgwc.net 참조
void save_graph(char *filename, int graph[][16], int num);

////////////////////////////////////////////////////////////////////////////////
// 깊이 우선 탐색 (초기 상태 -> 목적 상태)
void depth_first_search(int init_state, int goal_state) {
  int level = 0;
  int visited[16] = {
      0,
  };  // 방문한 정점을 저장

  dfs_main(init_state, goal_state, level, visited);
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
  int graph[16][16] = {
      0,
  };

  // 인접 행렬 만들기
  make_adjacency_matrix(graph);

  // 인접 행렬 출력 (only for debugging)
  // print_graph( graph, 16);

  // .net 파일 만들기
  save_graph("pwgc.net", graph, 16);

  // 깊이 우선 탐색
  depth_first_search(0, 15);  // initial state, goal state

  return 0;
}

void make_adjacency_matrix(int graph[16][16]) {
  int temp[16][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  for (int row = 0; row < 16; ++row) {
    for (int col = 0; col < 16; ++col) {
      graph[col][row] = temp[col][row];
    }
  }
}

void print_graph(int graph[][16], int num) {
  for (int row = 0; row < num; ++row) {
    for (int col = 0; col < 16; ++col) {
      printf("%d ", graph[col][row]);
    }
    printf("\n");
  }
}

void save_graph(char *filename, int graph[][16], int num) {
  FILE *graph_file = fopen(filename, "w");

  fprintf(graph_file, "*Vertices 16\n");
  for (int row = 0; row < num; ++row) {
    fprintf(graph_file, "%d \"", row + 1);
    print_statename(graph_file, row);
    fprintf(graph_file, "\"\n");
  }

  fprintf(graph_file, "*Edges\n");
  for (int row = 0; row < num; ++row) {
    for (int col = row; col < 16; ++col) {
      if (graph[col][row] == 1) {
        fprintf(graph_file, "  %d  %d\n", row + 1, col + 1);
      }
    }
  }
}

static void print_statename(FILE *fp, int state) {
  char states[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101",
                        "0110", "0111", "1000", "1001", "1010", "1011",
                        "1100", "1101", "1110", "1111"};

  fprintf(fp, "<%s>", states[state]);
}

static void get_pwgc(int state, int *p, int *w, int *g, int *c) {
  *p = state & PEASANT;
  *w = state & WOLF;
  *g = state & GOAT;
  *c = state & CABBAGE;
}

static int is_dead_end(int state) {
  int p = (state & PEASANT) / PEASANT;
  int w = (state & WOLF) / WOLF;
  int g = (state & GOAT) / GOAT;
  int c = (state & CABBAGE) / CABBAGE;

  if ((p == 0 && ((w == 1 && g == 1) || (g == 1 && c == 1))) ||
      (p == 1 && ((w == 0 && g == 0) || (g == 0 && c == 0)))) {
    printf("    next state ");
    print_statename(stdout, state);
    printf(" is dead-end\n");
    return 1;
  }

  return 0;
}

typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

BOOL same_direction(int state1, int state2) {
  int state_diff = state1 ^ state2;
  if (((state_diff | state1) == state1) || ((state_diff | state2) == state2)) {
    return TRUE;
  }
  return FALSE;
}

BOOL check_diff(int state1, int state2) {
  int state_diff = state1 ^ state2;
  int diff_count = 0;
  while (state_diff > 0) {
    if (state_diff % 2) {
      diff_count++;
    }
    state_diff /= 2;
  }

  if (diff_count > 2) {
    return FALSE;
  }
  return TRUE;
}

static int is_possible_transition(int state1, int state2) {
  return (same_direction(state1, state2) && (!is_dead_end(state2)) &&
          check_diff(state1, state2));
}

static int changeP(int state) {
  state ^= PEASANT;
  return state;
}

static int changePW(int state) {
  state ^= (PEASANT | WOLF);
  return state;
}

static int changePG(int state) {
  state ^= (PEASANT | GOAT);
  return state;
}

static int changePC(int state) {
  state ^= (PEASANT | CABBAGE);
  return state;
}

static int is_visited(int visited[], int level, int state) {
  if (state == 0 && level == 0) {
    return 0;
  }

  for (int idx = 0; idx < level; ++idx) {
    if (visited[idx] == state) {
      return 1;
    }
  }
  return 0;
}

static void print_states(int visited[], int count) {
  for (int idx = 0; idx < count; ++idx) {
    print_statename(stdout, visited[idx]);
    printf("\n");
  }
  printf("\n");
}

void change_state(int state, int next_state, int goal_state, int level,
                  int visited[]) {
  if (is_possible_transition(state, next_state)) {
    if (is_visited(visited, level, next_state)) {
      printf("    next state ");
      print_statename(stdout, next_state);
      printf(" has been visited\n");
    } else {
      dfs_main(next_state, goal_state, level, visited);
      printf("back to ");
      print_statename(stdout, state);
      printf(" (level %d)\n", level - 1);
    }
  }
}

static void dfs_main(int state, int goal_state, int level, int visited[]) {
  if (level > 16) {
    printf("err");
    return;
  }

  printf("cur state is ");
  print_statename(stdout, state);
  printf(" (level %d)\n", level);
  visited[level] = state;
  level++;

  if (state == goal_state) {
    printf("Goal-state found!\n");
    print_states(visited, level);
    return;
  }

  int next_state;

  next_state = changeP(state);
  change_state(state, next_state, goal_state, level, visited);

  next_state = changePW(state);
  change_state(state, next_state, goal_state, level, visited);

  next_state = changePG(state);
  change_state(state, next_state, goal_state, level, visited);

  next_state = changePC(state);
  change_state(state, next_state, goal_state, level, visited);
}