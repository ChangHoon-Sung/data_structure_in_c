#include <stdio.h>
#include <stdlib.h>

typedef int element;
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

ListNode* search_list(ListNode* head, element x) {
    ListNode* p = head;
    while (p != NULL) {
        if (p->data = x) return p;
        p = p->link;
    }
    return NULL;
}

ListNode* concatenate_list(ListNode* head1, ListNode* head2) {
    ListNode* p = head1;
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;

    while (p->link != NULL) p = p->link;
    p->link = head2;
    return head1;
}

ListNode* reverse_list(ListNode* head) {
    ListNode *p, *q, *r = NULL;  // p: 바꿀 리스트의 헤드, q: 바꿀 노드, r: 뒤집힌 리스트의 헤드
    p = head;

    while (p != NULL) {
        q = p;        // 바꿀 리스트의 헤드가 바꿀 노드가 된다.
        p = p->link;  // 바꿀 리스트의 헤드는 그 다음 노드를 가리킨다.

        q->link = r;  // 바꿀 노드는 바뀐 리스트의 헤드를 가리킨다.
        r = q;        // 바뀐 리스트의 헤드를 변경한다.
    }

    return r;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
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
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->data = 0;
    head->link = NULL;

    head = insert_first(head, 1);
    print_list(head);
    head = insert_first(head, 2);
    print_list(head);
    head = insert_first(head, 3);
    print_list(head);

    head = insert(head, head->link, 100);
    print_list(head);

    head = del(head, head);
    print_list(head);
    head = delete_first(head);
    print_list(head);

    printf("2nd data of list: %d\n", get_entry(head, 2)->data);
    printf("length of list: %d\n", get_length(head));
    printf("element %d was found from the list.\n\n", search_list(head, 100)->data);

    ListNode* head2;
    head2 = insert_first(head2, 30);
    head2 = insert_first(head2, 20);
    head2 = insert_first(head2, 10);
    printf("list2: ");
    print_list(head2);

    head = concatenate_list(head, head2);
    print_list(head);

    clear(head);
    clear(head2);

    return 0;
}