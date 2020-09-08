#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* next;
    struct DListNode* prev;
} DListNode;

void init(DListNode* head) {
    head->next = head;
    head->prev = head;
}

void print_dlist(DListNode* head) {
    DListNode* p;
    for (p = head->next; p != head; p = p->next) {
        printf("<-| |%d| |-> ", p->data);
    }
    printf("\n");
}

void insertAfter(DListNode* prev_node, element new_data) {
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    new_node->data = new_data;
    new_node->prev = prev_node;
    new_node->next = prev_node->next;
    prev_node->next->prev = new_node;
    prev_node->next = new_node;
}

void deleteNode(DListNode* head, DListNode* removed) {
    if (removed == head) return;
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    free(removed);
}

int main(void) {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    printf("추가\n");
    for (int i = 0; i < 5; i++) {
        insertAfter(head, i);
        print_dlist(head);
    }
    printf("\n");
    printf("제거\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        deleteNode(head, head->next);
    }
    free(head);
    return 0;
}