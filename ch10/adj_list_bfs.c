#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
int visited[MAX_VERTICES];

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

/* ============ 큐 ============*/
#define MAX_ELEMENT_SIZE 11

void error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

int is_full(Queue* q) {
    return ((q->rear + 1) % MAX_ELEMENT_SIZE == q->front);
}

int is_empty(Queue* q) {
    return (q->front == q->rear);
}

void enqueue(Queue* q, element e) {
    if (is_full(q)) {
        error("큐 포화 에러");
    }
    q->rear = (++q->rear) % MAX_ELEMENT_SIZE;
    q->data[q->rear] = e;
}

element dequeue(Queue* q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    q->front = (q->front + 1) % MAX_ELEMENT_SIZE;
    return q->data[q->front];
}

element peek(Queue* q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[(q->front + 1) % MAX_ELEMENT_SIZE];
}
/* ============ 큐 ============*/

void graph_init(GraphType* g) {
    int v;
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

void print_adj_list(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("정점 %d의 인접 리스트 ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

int get_degree(GraphType* g, int v) {
    GraphNode* p = g->adj_list[v];
    int degree = 0;

    while (p != NULL) {
        p = p->link;
        degree++;
    }

    return degree;
}

void bfs_list(GraphType* g, int v) {
    GraphNode* w = NULL;
    Queue q;
    init_queue(&q);

    visited[v] = TRUE;
    printf("%c 방문 -> ", v + 'A');
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);

        for (w = g->adj_list[v]; w != NULL; w = w->link) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = TRUE;
                printf("%c 방문 -> ", w->vertex + 'A');
                enqueue(&q, w->vertex);
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));

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
    bfs_list(g, 0);
    printf("\n");

    free(g);
    return 0;
}