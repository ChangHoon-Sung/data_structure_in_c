#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define False 0

/* ============ 큐 ============*/
#define MAX_ELEMENT_SIZE 11

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = 0;
}

int is_full(Queue *q) {
    return ((q->rear + 1) % MAX_ELEMENT_SIZE == q->front);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, element e) {
    if (is_full(q)) {
        error("큐 포화 에러");
    }
    q->rear = (++q->rear) % MAX_ELEMENT_SIZE;
    q->data[q->rear] = e;
}

element dequeue(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    q->front = (q->front + 1) % MAX_ELEMENT_SIZE;
    return q->data[q->front];
}

element peek(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[(q->front + 1) % MAX_ELEMENT_SIZE];
}
/* ============ 큐 ============*/

#define MAX_VERTICES 50
typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

void graph_init(GraphType *g) {
    memset(g->adj_mat, 0, sizeof(g->adj_mat));
    g->n = 0;
}

void insert_vertex(GraphType *g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점 개수 초과");
        exit(1);
    }
    g->n++;
}

void insert_edge(GraphType *g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 개수 초과");
        exit(1);
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void bfs_mat(GraphType *g, int v) {
    int w;
    Queue q;

    init_queue(&q);
    visited[v] = TRUE;
    printf("%d 방문 -> ", v);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d 방문 -> ", w);
                enqueue(&q, w);
            }
        }
    }
}

int main(void) {
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));

    graph_init(g);
    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}