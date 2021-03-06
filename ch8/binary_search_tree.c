#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;

// 노드 생성
TreeNode *new_node(int key) {
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode *min_value_node(TreeNode *node) {
    while (node->left != NULL) node = node->left;
    return node;
}

// 순환 탐색
TreeNode *search(TreeNode *node, int key) {
    if (!node) return NULL;

    if (key == node->key)
        return node;
    else if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

// 반복 탐색
TreeNode *iter_search(TreeNode *node, int key) {
    if (!node) return NULL;

    while (node != NULL) {
        if (key < node->key)
            node = node->left;
        else if (key > node->key)
            node = node->right;
        else
            return node;
    }
    return NULL;
}

// 삽입
TreeNode *insert(TreeNode *node, int key) {
    // 빈 트리인 경우 또는 삽입할 위치인 경우
    if (!node) return new_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

// 삭제
TreeNode *delete_node(TreeNode *node, int key) {
    TreeNode *temp = NULL;

    if (!node) return node;

    if (key < node->key)
        node->left = delete_node(node->left, key);
    else if (key > node->key)
        node->right = delete_node(node->right, key);
    else {
        if (!node->left) {
            temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            temp = node->left;
            free(node);
            return temp;
        }

        temp = min_value_node(node->right);
        node->key = temp->key;
        node->right = delete_node(node->right, temp->key);
    }

    return node;
}

// 중위 순회
void inorder_traversal(TreeNode *node) {
    if (node) {
        inorder_traversal(node->left);
        printf("%d->", node->key);
        inorder_traversal(node->right);
    }
}

int max(int n1, int n2) { return (n1 >= n2) ? n1 : n2; }

int get_height(TreeNode *root) {
    if (!root) return 0;
    return 1 + max(get_height(root->left), get_height(root->right));
}

int isBalanced(TreeNode *root) {
    int result, lh, rh;

    if (!root) return 1;

    lh = get_height(root->left);
    rh = get_height(root->right);
    printf("data: %d, left-tree's height: %d, right-tree's height: %d, gap: %d\n", root->key, lh, rh, abs(lh - rh));

    if (abs(lh - rh) <= 1) {
        return isBalanced(root->left) && isBalanced(root->right);
    } else {
        return 0;
    }
}

int sum(TreeNode *node) {
    if (!node) return 0;
    return node->key + sum(node->left) + sum(node->right);
}

int main(void) {
    int input[20] = {35, 18, 68, 7, 26, 99, 3, 12, 22, 30, 67, 100};
    TreeNode *root = NULL;

    for (int i = 0; i < 20; i++) {
        if (input[i])
            root = insert(root, input[i]);
    }

    if (isBalanced(root))
        printf("This tree is balanced.\n");
    else
        printf("This tree isn't balanced.\n");

    int total = 0;
    for (int i = 0; i < 20; i++)
        total += input[i];

    printf("Sum of keys: %d\n", sum(root));

    inorder_traversal(root);
    printf("\n");

    printf("delete element 12\n");
    root = delete_node(root, 12);

    inorder_traversal(root);
    printf("\n");

    printf("delete element 99\n");
    root = delete_node(root, 99);

    inorder_traversal(root);
    printf("\n");

    printf("delete element 22\n");
    root = delete_node(root, 22);

    inorder_traversal(root);
    printf("\n");

    printf("delete element 18\n");
    root = delete_node(root, 18);

    inorder_traversal(root);
    printf("\n");

    if (search(root, 30)) {
        printf("search result: element 30 exists in tree\n");
    } else {
        printf("search result: element 30 don't exists in tree\n");
    }

    if (iter_search(root, 40)) {
        printf("iter_search result: element 30 exists in tree\n");
    } else {
        printf("iter_search result: element 30 doesn't exist in tree\n");
    }
    return 0;
}