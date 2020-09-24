// BOJ 1991 트리 순회
// Assign: ChangHoon Sung
//
// INPUT
// N: 노드의 갯수 (1 <= N <= 26)
/*
TRY #1 (시간 초과)
루트 노드는 직접 할당하고, 이후에 들어오는 노드들은 트리 전체를 탐색해서 자식을 달아주었다.
그런데 이상하게 시간초과가 나왔다.

TRY #2 (정답)
루트 노드의 자식 노드가 2개 미만인 경우 예외처리를 잊고 있었다.
메모리 해제! 잊지 말자.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *create_node(char key) {
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void clear(TreeNode *node) {
    if (node) {
        if (node->left)
            clear(node->left);
        if (node->right)
            clear(node->right);
        free(node);
    }
}

void inorder(TreeNode *node) {
    if (node) {
        inorder(node->left);
        printf("%c", node->key);
        inorder(node->right);
    }
}

void postorder(TreeNode *node) {
    if (node) {
        printf("%c", node->key);
        postorder(node->left);
        postorder(node->right);
    }
}

void preorder(TreeNode *node) {
    if (node) {
        preorder(node->left);
        preorder(node->right);
        printf("%c", node->key);
    }
}

TreeNode *find_node(TreeNode *node, char key) {
    TreeNode *l = NULL, *r = NULL;

    // 중위 순회 이용
    if (node) {
        if (node->key == key) return node;

        l = find_node(node->left, key);
        if (l) return l;

        r = find_node(node->right, key);
        if (r) return r;
    }

    return NULL;
}

TreeNode *insert_node(TreeNode *root, char root_key, char left_key, char right_key) {
    TreeNode *node = NULL;

    if (!root) {
        root = create_node(root_key);
        if (left_key != '.') root->left = create_node(left_key);
        if (right_key != '.') root->right = create_node(right_key);
        return root;
    }

    node = find_node(root, root_key);
    if (node) {
        if (left_key != '.') node->left = create_node(left_key);
        if (right_key != '.') node->right = create_node(right_key);
    }
    return root;
}

int main(void) {
    int N;
    char c, l, r;
    TreeNode *root = NULL;

    scanf("%d", &N);
    getchar();

    for (int i = 0; i < N; i++) {
        scanf("%c %c %c", &c, &l, &r);
        getchar();
        root = insert_node(root, c, l, r);
    }

    postorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    preorder(root);

    clear(root);

    return 0;
}