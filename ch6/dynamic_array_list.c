#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element *array;
    int size;
    int capacity;
} ArrayList;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void init(ArrayList *L) {
    L->size = 0;
    L->capacity = 1;
    L->array = (element *)malloc(sizeof(element) * L->capacity);
}

int is_empty(ArrayList *L) {
    return (L->size == 0);
}

int is_full(ArrayList *L) {
    return (L->size == L->capacity);
}

void expand_double(ArrayList *L) {
    L->capacity *= 2;
    L->array = (element *)realloc(L->array, sizeof(element) * L->capacity);
}

element get_entry(ArrayList *L, int pos) {
    if (pos < 0 || pos > L->capacity) {
        error("index out of max size");
    }
    return L->array[pos];
}

void print_list(ArrayList *L) {
    printf("size: %d capacity: %d\n", L->size, L->capacity);
    for (int i = 0; i < L->size; i++) {
        printf("%d->", L->array[i]);
    }
    printf("\n\n");
}

void insert_last(ArrayList *L, element e) {
    if (is_full(L))
        expand_double(L);
    L->array[L->size++] = e;
}

void insert_first(ArrayList *L, element e) {
    if (is_full(L))
        expand_double(L);

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

void clear(ArrayList *L) {
    L->size = 0;
}

void replace(ArrayList *L, int pos, element e) {
    L->array[pos] = e;
}

void get_length(ArrayList *L) {
    return L->size;
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
    clear(&list);
    print_list(&list);
    insert_first(&list, 10);
    print_list(&list);
    insert_first(&list, 20);
    print_list(&list);
    insert_first(&list, 30);
    print_list(&list);
    insert_last(&list, 40);
    return 0;
}