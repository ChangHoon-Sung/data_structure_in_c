#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 100

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

typedef struct {
    struct ListNode *head;
    struct ListNode *tail;
    int size;
} SortedList;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

//init
void init(SortedList *l) {
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
}

//is_empty
int is_empty(SortedList *l) {
    return (l->size == 0);
}

//is_full
int is_full(SortedList *l) {
    return l->size == MAX_ELEMENT_SIZE;
}

//add(list, item) - O(N)
ListNode *add(SortedList *l, element item) {
    ListNode *i = l->head;
    ListNode *prev = NULL;

    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = item;
    p->link = NULL;

    if (is_empty(l)) {
        l->head = p;
        l->tail = p;
    } else {
        while (i->data < item) {
            prev = i;
            i = i->link;
        }
        if (i == l->head) {
            p->link = l->head;
            l->size++;
            return p;
        } else {
            p->link = prev->link;
            prev->link = p;
        }
    }
    l->size++;
    return l->head;
}

//is_in_list(list, item) - O(N)
int is_in_list(SortedList *l, element item) {
    ListNode *i = l->head;
    while (i->link != NULL && i->data < item) i = i->link;
    return (i->data == item);
}

//del(list, item) - O(N)
ListNode *del(SortedList *l, element item) {
    ListNode *i = l->head;
    ListNode *prev = NULL;

    if (!is_in_list(l, item)) error("can't find such element");
    l->size--;
    while (i->data < item) {
        prev = i;
        i = i->link;
    }
    if (i == l->head) {
        i = l->head->link;
        free(l->head);
        return i;
    } else {
        prev->link = i->link;
        free(i);
    }
    return l->head;
}

//clear
void clear(SortedList *l) {
    ListNode *removed;
    for (ListNode *p = l->head; p != NULL; p = p->link) {
        removed = p;
        free(removed);
    }
    init(l);
}

//get_length
int get_length(SortedList *l) {
    return l->size;
}

//display
void display(SortedList *l) {
    if (is_empty(l)) printf("Empty");
    for (ListNode *i = l->head; i != NULL; i = i->link) {
        printf("%d->", i->data);
    }
    printf("\n");
}

int main(void) {
    SortedList list;
    init(&list);

    list.head = add(&list, 241);
    display(&list);
    list.head = add(&list, 21);
    display(&list);
    list.head = add(&list, 41);
    display(&list);
    list.head = add(&list, 1);
    display(&list);
    list.head = add(&list, 2);
    display(&list);

    list.head = del(&list, 241);
    display(&list);
    list.head = del(&list, 1);
    display(&list);
    list.head = del(&list, 21);
    display(&list);

    printf("length of list: %d\n", get_length(&list));
    clear(&list);
    display(&list);
    return 0;
}