#include <stdio.h>

#define LEFT(x) 2 * x
#define RIGHT(x) 2 * x + 1

void preorder_traversal(int arr[], int idx) {
    if (arr[idx] != 0) {
        printf("%d ", arr[idx]);
        preorder_traversal(arr, LEFT(idx));
        preorder_traversal(arr, RIGHT(idx));
    }
}

void inorder_traversal(int arr[], int idx) {
    if (arr[idx] != 0) {
        inorder_traversal(arr, LEFT(idx));
        printf("%d ", arr[idx]);
        inorder_traversal(arr, RIGHT(idx));
    }
}

void postorder_traversal(int arr[], int idx) {
    if (arr[idx] != 0) {
        postorder_traversal(arr, LEFT(idx));
        postorder_traversal(arr, RIGHT(idx));
        printf("%d ", arr[idx]);
    }
}

int main(void) {
    int arr[100] = {};
    for (int i = 1; i < 8; i++) {
        arr[i] = i;
    }

    printf("linear print: ");
    for (int i = 1; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("preorder print: ");
    preorder_traversal(arr, 1);
    printf("\n");

    printf("inorder print: ");
    inorder_traversal(arr, 1);
    printf("\n");

    printf("postorder print: ");
    postorder_traversal(arr, 1);
    printf("\n");

    return 0;
}