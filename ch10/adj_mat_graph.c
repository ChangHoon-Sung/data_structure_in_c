#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50

int visited[MAX_VERTICES];

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void init_graph(GraphType *g) {
    memset(g->adj_mat, 0, sizeof(g->adj_mat));
}

void insert_vertex(GraphType *g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType *g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

int get_degree(GraphType *g, int v) {
    int degree = 0;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[v][i]) degree++;
    }
    return degree;
}

void dfs_mat(GraphType *g, int v) {
    visited[v] = 1;
    printf("정점 %d -> ", v);
    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_mat(g, w);
        }
    }
}

int main(void) {
    GraphType *graph = (GraphType *)malloc(sizeof(GraphType));
    init_graph(graph);

    for (int i = 0; i < 4; i++) {
        insert_vertex(graph, i);
    }

    insert_edge(graph, 0, 1);
    insert_edge(graph, 0, 2);
    insert_edge(graph, 0, 3);
    insert_edge(graph, 1, 2);
    insert_edge(graph, 2, 3);
    print_adj_mat(graph);

    for (int v = 0; v < graph->n; v++) {
        printf("정점 %d의 차수: %d\n", v, get_degree(graph, v));
    }

    printf("DFS\n");
    dfs_mat(graph, 0);
    printf("\n");

    free(graph);
    return 0;
}