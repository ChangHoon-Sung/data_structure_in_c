#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
int parent[MAX_VERTICES];

int printMST(GraphType* g, int parent[]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < g->n; i++)
        printf("%d - %d \t%d \n", parent[i], i, g->weight[i][parent[i]]);
}

int get_min_vertex(int n) {
    int min_idx, min_value = INF;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (distance[i] < min_value)) {
            min_idx = i, min_value = distance[i];
        }
    }
    return min_idx;
}

void prim(GraphType* g, int s) {
    int i, u, v;

    // distance 초기화
    for (int u = 0; u < g->n; u++) {
        distance[u] = INF;
    }
    // 시작 정점의 거리 초기화
    distance[s] = 0;
    parent[s] = -1;

    for (int i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);

        // 만약 트리 집합과 가장 가까운 노드까지의 거리가 무한이면 스패닝 트리를 만들 수 없다.
        // 무한이 아니라면, 그 노드를 추가한다. (그리디 알고리즘)
        if (distance[u] == INF)
            return;
        else {
            selected[u] = TRUE;
            printf("정점 %d 추가\n", u);
        }

        // 추가한 노드 u의 모든 인접한 노드 v를 조사하여 distance를 업데이트한다.
        // 이때 인접한 노드 v는 u와 연결되어 있고, 스패닝 트리에 속하지 않아야 하며
        // u-v 간선의 가중치는 distance[v]보다 작아야 한다.
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
                parent[v] = u;
            }
        }
    }
}

int main(void) {
    GraphType g = {
        8,
        {
            {0, 10, INF, 6, INF, INF, INF, 1},
            {10, 0, 4, INF, INF, 2, INF, INF},
            {INF, 4, 0, 11, INF, 7, INF, INF},
            {6, INF, 11, 0, INF, INF, INF, 3},
            {INF, INF, INF, INF, 0, 5, INF, 8},
            {INF, 2, 7, INF, 5, 0, 9, INF},
            {INF, INF, INF, INF, INF, 9, 0, 12},
            {1, INF, INF, 3, 8, INF, 12, 0},
        },
    };

    prim(&g, 0);
    printf("\n");
    printMST(&g, parent);

    return 0;
}