#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) {
    if (top < SIZE - 1) stack[++top] = p;
}

TreeNode* pop(void) {
    TreeNode* p = NULL;
    if (top >= 0) p = stack[top--];
    return p;
}

void inorder_iter(TreeNode* root) {
    while (1) {
        for (; root != NULL; root = root->left) {
            push(root);
        }
        root = pop();
        if (root == NULL) break;
        printf("[%d] ", root->data);
        root = root->right;
    }
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->data);
        inorder(root->right);
    }
    return;
}

int main(void) {
    TreeNode n10 = {22, NULL, NULL};
    TreeNode n7 = {95, NULL, NULL};
    TreeNode n6 = {35, &n10, NULL};
    TreeNode n4 = {5, NULL, NULL};
    TreeNode n3 = {93, &n6, &n7};
    TreeNode n2 = {15, &n4, NULL};
    TreeNode n1 = {17, &n2, &n3};

    TreeNode* root = &n1;

    printf("inorder print: \t\t");
    inorder(root);
    printf("\n");

    printf("inorder_iter print: \t");
    inorder_iter(root);
    printf("\n");

    return 0;
}