#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;  // 헤드가 마지막 노드인 변형된 원형 링크드 리스트

int is_empty(ListNode* head) {
    return (head == NULL);
}

ListNode* insert_first(ListNode* head, element item) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = item;
    if (head == NULL) {
        head = node;
        node->link = head;
    } else {
        node->link = head->link;
        head->link = node;
    }

    return head;
}

ListNode* insert_last(ListNode* head, element item) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = item;
    if (head == NULL) {
        head = node;
        node->link = head;
    } else {
        node->link = head->link;
        head->link = node;
        head = node;
    }

    return head;
}

ListNode* delete_node(ListNode* head, element item) {
    ListNode *curr = head, *prev = NULL;

    // 빈 리스트이면
    if (head == NULL)
        return NULL;

    // 단일 노드 리스트이면
    if (head->link == head) {
        free(head);
        return NULL;
    }

    // 노드 찾기
    while (curr->data != item) {
        if (curr->link == head) {
            printf("element not found.\n");
        }
        prev = curr;
        curr = curr->link;
    }

    // 만약 마지막 노드이면
    if (curr == head) {
        prev = head;
        while (prev->link != head) prev = prev->link;
        prev->link = curr->link;
        head = prev;
        free(curr);
    } else {  // 나머지 경우
        prev->link = curr->link;
        free(curr);
    }

    return head;
}

int get_length(ListNode* head) {
    ListNode* p = head;
    int cnt = 0;

    if (is_empty(head)) return 0;
    do {
        cnt++;
        p = p->link;
    } while (p != head);

    return cnt;
}

void print_list(ListNode* head) {
    ListNode* p;

    if (is_empty(head)) return;
    p = head->link;
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head);
    printf("%d->\n", p->data);
}

int main(void) {
    ListNode* head;  // 헤드는 마지막 노드이다.

    head = insert_first(head, 100);
    printf("length of list: %d\n", get_length(head));
    head = insert_last(head, 200);
    printf("length of list: %d\n", get_length(head));
    head = insert_last(head, 300);
    printf("length of list: %d\n", get_length(head));
    head = insert_first(head, 400);
    printf("length of list: %d\n", get_length(head));
    head = insert_first(head, 500);
    printf("length of list: %d\n", get_length(head));
    print_list(head);

    head = delete_node(head, 300);
    print_list(head);
    head = delete_node(head, 500);
    print_list(head);
    head = delete_node(head, 100);
    print_list(head);
    return 0;
}