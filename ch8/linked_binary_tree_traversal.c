#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("[%d] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
    return;
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->data);
        inorder(root->right);
    }
    return;
}

void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("[%d] ", root->data);
    }
    return;
}

int main(void) {
    TreeNode n5 = {5, NULL, NULL};
    TreeNode n4 = {4, NULL, NULL};
    TreeNode n3 = {3, NULL, NULL};
    TreeNode n2 = {2, &n4, &n5};
    TreeNode n1 = {1, &n2, &n3};

    TreeNode* root = &n1;

    printf("preorder print: ");
    preorder(root);
    printf("\n");

    printf("inorder print: ");
    inorder(root);
    printf("\n");

    printf("postorder print: ");
    postorder(root);
    printf("\n");

    return 0;
}