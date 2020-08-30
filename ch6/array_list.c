#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 100

typedef int element;
typedef struct {
    element array[MAX_ELEMENT_SIZE];
    int size;
} ArrayList;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void init(ArrayList *L) {
    L->size = 0;
}

int is_empty(ArrayList *L) {
    return (L->size == 0);
}

int is_full(ArrayList *L) {
    return (L->size == MAX_ELEMENT_SIZE);
}

element get_entry(ArrayList *L, int pos) {
    if (pos < 0 || pos > MAX_ELEMENT_SIZE) {
        error("index out of max size");
    }
    return L->array[pos];
}

void print_list(ArrayList *L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d->", L->array[i]);
    }
    printf("\n");
}

void insert_last(ArrayList *L, element e) {
    if (is_full(L)) {
        error("list overflow");
    }
    L->array[L->size++] = e;
}

void insert_first(ArrayList *L, element e) {
    if (is_full(L))
        error("list overflow");

    for (int i = L->size - 1; i >= 0; i--) {
        L->array[i + 1] = L->array[i];
    }
    L->array[0] = e;
    L->size++;
}

void insert(ArrayList *L, int pos, element e) {
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        for (int i = L->size - 1; i >= pos; i--) {
            L->array[i + 1] = L->array[i];
        }
        L->array[pos] = e;
        L->size++;
    }
}

element remove(ArrayList *L, int pos) {
    element item;

    if (!is_empty(L) && (pos >= 0) && (pos <= L->size)) {
        item = L->array[pos];

        for (int i = pos; i < L->size; i++) {
            L->array[i] = L->array[i + 1];
        }

        L->size--;
    }

    return item;
}

int main(void) {
    ArrayList list;

    init(&list);
    insert_first(&list, 10);
    print_list(&list);
    insert_first(&list, 20);
    print_list(&list);
    insert_first(&list, 30);
    print_list(&list);
    insert_last(&list, 40);
    print_list(&list);
    remove(&list, 0);
    print_list(&list);
    return 0;
}