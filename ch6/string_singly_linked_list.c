#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];  // 반드시 자료는 element를 통해 구조가 결정되어야 한다.
} element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element new_item) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = new_item;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* prev, element new_item) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = new_item;
    p->link = prev->link;
    prev->link = p;
    return head;
}

ListNode* delete_first(ListNode* head) {
    ListNode* removed;
    if (head == NULL) return NULL;

    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode* del(ListNode* head, ListNode* prev) {
    ListNode* removed;
    removed = prev->link;
    prev->link = removed->link;
    free(removed);
    return head;
}

ListNode* get_entry(ListNode* head, int idx) {
    ListNode* p = head;
    while (--idx) {
        p = p->link;
    }
    return p;
}

int get_length(ListNode* head) {
    ListNode* p = head;
    int cnt = 0;

    while (p != NULL) {
        p = p->link;
        cnt++;
    }
    return cnt;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%s->", p->data.name);
    }
    printf("NULL\n");
}

void clear(ListNode* head) {
    for (ListNode* p = head; p != NULL;) {
        ListNode* q = p->link;
        free(p);
        p = q;
    }
}

int main(void) {
    ListNode* head = NULL;
    element data;

    strcpy(data.name, "APPLE");  // 문자열을 다루는 경우 반드시 함수로 안전하게 복사하는 것을 잊지 말자.
    head = insert_first(head, data);

    strcpy(data.name, "BANANA");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "CHARLIE");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "DAGGER");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "TOMATO");
    head = insert(head, head->link, data);
    print_list(head);

    head = del(head, head);
    print_list(head);
    head = delete_first(head);
    print_list(head);

    printf("2nd data of list: %s\n", get_entry(head, 2)->data.name);
    printf("length of list: %d\n", get_length(head));

    clear(head);

    return 0;
}