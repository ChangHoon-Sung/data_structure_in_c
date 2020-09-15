#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

#define MAX_ELEMENT_SIZE 100

typedef TreeNode *element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

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

void level_order(TreeNode *ptr) {
    Queue q;
    init_queue(&q);

    if (ptr == NULL) return;
    enqueue(&q, ptr);
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf(" [%d] ", ptr->data);
        if (ptr->left != NULL) enqueue(&q, ptr->left);
        if (ptr->right != NULL) enqueue(&q, ptr->right);
    }
}

int main(void) {
    TreeNode n10 = {22, NULL, NULL};
    TreeNode n7 = {95, NULL, NULL};
    TreeNode n6 = {35, &n10, NULL};
    TreeNode n4 = {5, NULL, NULL};
    TreeNode n3 = {93, &n6, &n7};
    TreeNode n2 = {15, &n4, NULL};
    TreeNode n1 = {17, &n2, &n3};

    TreeNode *root = &n1;

    printf("level order print: ");
    level_order(root);
    printf("\n");

    return 0;
}