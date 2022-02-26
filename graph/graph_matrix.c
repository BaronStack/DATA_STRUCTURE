#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAPH (1 << 8)

int *graph[MAX_GRAPH];

void init_graph(int size) {
  if (size > MAX_GRAPH) {
    return;
  }

  int i = 0;
  int j = 0;
  for (; i < size; ++i) {
    graph[i] = (int *)malloc(size * sizeof(int));
    for (; j < size; ++j) {
      graph[i][j] = 0;
    }
  }
}

void add_edge(int v1, int v2) {
  graph[v1][v2] = 1;
  graph[v2][v1] = 1;
}

void print_graph(int size) {
  int i = 0;
  int j = 0;
  for (; i < size; ++i) {
    for (; j < size; ++j) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}

/*
  1 ----- 2 ----- 3
  |     / |     /
  |    /  |    /
  |   /   |   /
  |  /    |  /
  | /     | /
  4 ----- 5
*/
void create_graph(int size) {
  init_graph(size);

  add_edge(0, 1);
  add_edge(0, 3);

  add_edge(1, 0);
  add_edge(1, 2);
  add_edge(1, 3);
  add_edge(1, 4);

  add_edge(2, 1);
  add_edge(2, 4);

  add_edge(3, 0);
  add_edge(3, 1);
  add_edge(3, 4);

  add_edge(4, 1);
  add_edge(4, 2);
  add_edge(4, 3);
}

int main() {
  create_graph(6);
  print_graph(6);

  return 0;
}