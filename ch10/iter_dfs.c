#include <stdio.h>
#include <stdlib.h>

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

void init_graph(GraphType* g) {
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

void dfs_list(GraphType* g, int v) {
    visited[v] = 1;
    printf("정점 %d -> ", v);

    for (GraphNode* w = g->adj_list[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs_list(g, w->vertex);
        }
    }
}

/*======스택======*/
typedef GraphNode* element;
typedef struct Stack {
    int data[MAX_VERTICES];
    int top;
} Stack;

void init_stack(Stack* s) {
    s->top = -1;
}

int is_empty(Stack* s) { return (s->top == -1); }

void push(Stack* s, element e) {
    s->data[++(s->top)] = e;
}

element pop(Stack* s) {
    return s->data[(s->top)--];
}
/*======스택======*/

void dfs_iterative(GraphType* g, element v) {
    Stack s;
    element w;
    init_stack(&s);

    push(&s, v);
    while (!is_empty(&s)) {
        w = pop(&s);
        if (!visited[w->vertex]) {
            printf("정점 %d 방문 -> ", w->vertex);
            visited[w->vertex] = 1;
            for (element u = w->link; u; u = u->link) {
                if (!visited[u->vertex]) {
                    push(&s, u);
                }
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init_graph(g);
    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    print_adj_list(g);

    for (int v = 0; v < g->n; v++) {
        printf("정점 %d의 차수: %d\n", v, get_degree(g, v));
    }

    printf("DFS\n");
    dfs_list(g, 0);
    printf("\n");

    printf("DFS - iter\n");
    dfs_iterative(g, g->adj_list[0]);
    printf("\n");

    free(g);
    return 0;
}