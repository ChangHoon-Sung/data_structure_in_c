#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int size;
} SortedList;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

//init
void init(SortedList *l) {
    l->size = 0;
}

//is_empty
int is_empty(SortedList *l) {
    return !(l->size);
}

//is_full
int is_full(SortedList *l) {
    return l->size == MAX_ELEMENT_SIZE;
}

//add(list, item) - O(N)
void add(SortedList *l, element item) {
    int idx = 0;
    if (is_empty(l))
        l->data[0] = item;
    else if (item >= l->data[l->size - 1]) {
        l->data[l->size] = item;
    } else {
        while (l->data[idx] < item) idx++;

        for (int i = l->size - 1; i >= idx; i--) {
            l->data[i + 1] = l->data[i];
        }
        l->data[idx] = item;
    }
    l->size++;
    return;
}

//is_in_list(list, item) - O(N)
int is_in_list(SortedList *l, element item) {
    int i;
    for (i = 0; l->data[i] != item && i < l->size; i++)
        continue;
    return !(i == l->size);
}

//del(list, item) - O(N)
void del(SortedList *l, element item) {
    int idx = 0;
    if (!is_in_list(l, item)) error("can't find such element");
    while (l->data[idx] < item) idx++;

    for (int i = idx; i < l->size; i++) {
        l->data[i] = l->data[i + 1];
    }
    l->size--;
    return;
}

//clear
void clear(SortedList *l) {
    l->size = 0;
}

//get_length
int get_length(SortedList *l) {
    return l->size;
}

//display
void display(SortedList *l) {
    if (is_empty(l)) printf("Empty");
    for (int i = 0; i < l->size; i++) {
        printf("%d->", l->data[i]);
    }
    printf("\n");
}

int main(void) {
    SortedList list;
    init(&list);

    add(&list, 241);
    add(&list, 21);
    add(&list, 41);
    add(&list, 1);
    add(&list, 2);
    display(&list);

    del(&list, 241);
    display(&list);

    printf("length of list: %d\n", get_length(&list));
    clear(&list);
    display(&list);
    return 0;
}