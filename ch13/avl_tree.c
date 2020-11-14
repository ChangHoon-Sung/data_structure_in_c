#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *create_node(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

AVLNode *rotate_right(AVLNode *parent) {
    AVLNode *child = parent->left;
    parent->left = child->right;
    child->right = parent;
    return child;
}

AVLNode *rotate_left(AVLNode *parent) {
    AVLNode *child = parent->right;
    parent->right = child->left;
    child->left = parent;
    return child;
}

int get_height(AVLNode *node) {
    if (node != NULL) {
        return 1 + max(get_height(node->left), get_height(node->right));
    }
}

int get_balance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);
}

AVLNode *insert(AVLNode *node, int key) {
    int balance;

    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    balance = get_balance(node);

    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }
    if (balance > 1 && key > node->right->key) {
        node->left = rotate_left(node);
        return rotate_right(node);
    }
    if (balance < -1 && key < node->left->key) {
        node->right = rotate_right(node);
        return rotate_left(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }

    return node;
}