#include <stdio.h>
#include <time.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
    int is_thread;
} TreeNode;

TreeNode* find_successor(TreeNode* node) {
    TreeNode* p;

    // node->right == NULL 은 현재 노드가 트리의 가장 하단 우측에 있다는 뜻이다.
    if (!node->right || node->is_thread == 1) {
        return node->right;
    } else {
        p = node->right;
        while (p->left) p = p->left;
        return p;
    }
}

void thread_inorder_traversal(TreeNode* node) {
    TreeNode* q = node;

    while (q->left) q = q->left;
    do {
        printf("%c ", q->data);
        q = find_successor(q);
    } while (q);
}

void inorder_traversal(TreeNode* node) {
    if (node) {
        inorder_traversal(node->left);
        printf("%c ", node->data);
        inorder_traversal(node->right);
    }
}

int main(void) {
    TreeNode n1 = {'A', NULL, NULL, 1};
    TreeNode n2 = {'B', NULL, NULL, 1};
    TreeNode n3 = {'C', &n1, &n2, 0};
    TreeNode n4 = {'D', NULL, NULL, 1};
    TreeNode n5 = {'E', NULL, NULL, 0};
    TreeNode n6 = {'F', &n4, &n5, 0};
    TreeNode n7 = {'G', &n3, &n6, 0};

    TreeNode* root = &n7;

    clock_t start, end;

    printf("inorder traversal: ");
    start = clock();
    inorder_traversal(root);
    end = clock();
    printf("\n");
    printf("takes %lf times\n", (double)(end - start) / CLOCKS_PER_SEC);

    // pre-process
    printf("\n");
    n1.right = &n3;
    n2.right = &n7;
    n4.right = &n6;

    printf("thread inorder traversal: ");
    start = clock();
    thread_inorder_traversal(root);
    end = clock();
    printf("\n");
    printf("takes %lf times\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}