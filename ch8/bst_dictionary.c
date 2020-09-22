#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
    char word[100];
    char mean[100];
} element;

typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

int compare(element e1, element e2) {
    return strcmp(e1.word, e2.word);
}

void print_dict(TreeNode *node) {
    if (node) {
        print_dict(node->left);
        printf("단어: %10s  |  의미: %s\n", node->key.word, node->key.mean);
        print_dict(node->right);
    }
}

TreeNode *insert(TreeNode *node, element key) {
    if (!node) {
        TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
        new_node->key = key;
        printf("[insert] '%s' sucessfully added on dictionary!\n", new_node->key.word);
        return new_node;
    }

    if (compare(key, node->key) < 0) {
        node->left = insert(node->left, key);
    } else if (compare(key, node->key) > 0) {
        node->right = insert(node->right, key);
    } else {
        printf("[insert] key already exists!\n");
    }

    return node;
}

TreeNode *search(TreeNode *node, element key) {
    while (node) {
        if (compare(key, node->key) < 0) {
            node = node->left;
        } else if (compare(key, node->key) > 0) {
            node = node->right;
        } else
            return node;
    }

    return NULL;
}

TreeNode *min_value_node(TreeNode *node) {
    while (node) node = node->left;
    return node;
}

TreeNode *delete_node(TreeNode *node, element key) {
    TreeNode *temp = NULL;
    if (!node) return NULL;

    if (compare(key, node->key) < 0) {
        node->left = delete_node(node->left, key);
    } else if (compare(key, node->key) > 0) {
        node->right = delete_node(node->right, key);
    } else {
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
        node = delete_node(node->right, temp->key);
    }
    return node;
}

int main(void) {
    TreeNode *root = NULL, *result = NULL;
    char cmd;
    element new_word;

    printf("pre-processing...\n");
    snprintf(new_word.word, sizeof(new_word), "apple");
    snprintf(new_word.mean, sizeof(new_word), "사과");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "banana");
    snprintf(new_word.mean, sizeof(new_word), "바나나");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "Zimbabwe");
    snprintf(new_word.mean, sizeof(new_word), "짐바브웨");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "Yankee");
    snprintf(new_word.mean, sizeof(new_word), "북아메리카에 거주하는 사람을 일컫는 말");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "jealous");
    snprintf(new_word.mean, sizeof(new_word), "질투");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "anger");
    snprintf(new_word.mean, sizeof(new_word), "화");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "irony");
    snprintf(new_word.mean, sizeof(new_word), "모순적인");
    root = insert(root, new_word);
    snprintf(new_word.word, sizeof(new_word), "envy");
    snprintf(new_word.mean, sizeof(new_word), "부러움");
    root = insert(root, new_word);
    printf("done!\n\n\n");

    do {
        printf("\n--- 입력: i | 삭제: d | 탐색: s | 출력: p | 종료: q ---\n");
        printf(">> ");
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                printf("단어: ");
                scanf("%s", new_word.word);
                printf("의미: ");
                scanf("%s", new_word.mean);

                root = insert(root, new_word);
                break;

            case 'd':
                printf("단어: ");
                scanf("%s", new_word.word);

                if (search(root, new_word)) {
                    root = delete_node(root, new_word);
                    printf("'%s' sucessfully deleted.\n", new_word.word);
                } else
                    printf("Can't find '%s' in dictionary.\n", new_word.word);
                break;

            case 's':
                printf("단어: ");
                scanf("%s", new_word.word);

                result = search(root, new_word);

                if (result)
                    printf("의미: %s\n", result->key.mean);
                else
                    printf("Can't find '%s' in dictionary.\n", new_word.word);
                break;

            case 'p':
                print_dict(root);
                printf("\n");
                break;

            case 'q':
                printf("사전을 종료합니다.\n");
                exit(0);

            default:
                printf("알 수 없는 명령어\n");
                break;
        }

        while (getchar() != '\n') continue;  // insert와 cmd 입력 후 버퍼 비우기

    } while (1);

    return 0;
}