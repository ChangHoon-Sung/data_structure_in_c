#include <stdio.h>

#define max(x, y) (((x) >= (y)) ? (x) : (y))

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

int get_node_count(TreeNode* node) {
    if (node) return 1 + get_node_count(node->left) + get_node_count(node->right);
}

int get_leafnode_count(TreeNode* node) {
    if (node) {
        if (!node->left && !node->right)
            return 1;
        else
            return get_leafnode_count(node->left) + get_leafnode_count(node->right);
    }
}

int get_internal_node_count(TreeNode* node) {
    if (!node || (!node->left && !node->right))
        return 0;
    else
        return 1 + get_leafnode_count(node->left) + get_leafnode_count(node->right);
}

int get_height(TreeNode* node) {
    if (node)
        return 1 + max(get_height(node->left), get_height(node->right));
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

    printf("preorder print: ");
    preorder(root);
    printf("\n");

    printf("inorder print: ");
    inorder(root);
    printf("\n");

    printf("postorder print: ");
    postorder(root);
    printf("\n");

    printf("count of node: %d\n", get_node_count(root));
    printf("count of leafnode: %d\n", get_leafnode_count(root));
    printf("count of internal_node: %d\n", get_internal_node_count(root));

    printf("height of node: %d\n", get_height(root));
    return 0;
}