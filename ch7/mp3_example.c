#include <stdio.h>
#include <stdlib.h>

typedef char element[100];
typedef struct DListNode {
    element data;
    struct DListNode* next;
    struct DListNode* prev;
} DListNode;

DListNode* current;

void init(DListNode* head) {
    head->next = head;
    head->prev = head;
}

void print_dlist(DListNode* head) {
    DListNode* p;
    for (p = head->next; p != head; p = p->next) {
        if (p == current)
            printf("<-| # %s # |-> ", p->data);
        else
            printf("<-| %s |-> ", p->data);
    }
    printf("\n");
}

void insertAfter(DListNode* prev_node, element new_data) {
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    snprintf(new_node->data, sizeof(new_node->data), "%s", new_data);
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

void clear(DListNode* head) {
    DListNode *p = head->next, *q = NULL;
    while (p != head) {
        q = p->next;
        free(p);
        p = q;
    }
    init(head);
}

int main(void) {
    char cmd;
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    insertAfter(head, "Mamamia");
    insertAfter(head, "Dancing Queen");
    insertAfter(head, "Fernando");

    current = head->next;
    print_dlist(head);

    do {
        printf("Enter the command(<, >, q): ");
        cmd = getchar();
        getchar();
        printf("\n");
        switch (cmd) {
            case '<':
                current = current->prev;
                if (current == head) current = current->prev;
                break;
            case '>':
                current = current->next;
                if (current == head) current = current->next;
                break;
        }
        if (cmd != 'q') print_dlist(head);

    } while (cmd != 'q');

    clear(head);
    return 0;
}