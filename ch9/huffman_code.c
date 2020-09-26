/*
Huffman code
문자의 빈도가 알려진 문자열의 압축에 사용된다.
빈도가 높을 수록 짧은 비트열이 부여되고, 낮을 수록 긴 비트열이 부여된다.
각 비트열은 다른 비트열의 prefix가 아니기 때문에 복호시 중복이 발생하거나 잘못 해석할 염려가 없다.
최소 힙을 사용한다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left, *right;
} TreeNode;  // 빈도와 가중치에 따라 생성되는 트리의 노드. 이 트리의 간선 가중치에 따라 허프만 코드가 생성된다.

typedef struct element {
    TreeNode *ptree;
    int key;
} element;  // 힙의 원소. 단일 노드 혹은 트리를 가리킨다.

typedef struct Heap {
    element heap[MAX_ELEMENT];
    int heap_size;
} Heap;

Heap *create() {
    return (Heap *)malloc(sizeof(Heap));
}

void init_heap(Heap *h) {
    h->heap_size = 0;
}

void insert_min_heap(Heap *h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(Heap *h) {
    element item = h->heap[1];
    element temp = h->heap[(h->heap_size--)];
    int parent = 1, child = 2;
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

TreeNode *make_tree(TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    node->weight = 0;
    node->ch = 0;
    return node;
}

void clear_tree(TreeNode *node) {
    if (node) {
        clear_tree(node->left);
        clear_tree(node->right);
        free(node);
    }
}

int is_leaf(TreeNode *node) {
    return !node->left && !node->right;
}

void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);

    printf("\n");
}

void print_codes(TreeNode *root, int codes[], int top) {
    // 모든 단말 노드를 출력하는 코드
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

void huffman_tree(int freq[], char ch_list[], int n) {
    int i;
    TreeNode *node, *x;
    Heap *heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();
    init_heap(heap);

    // 노드를 만들고, 힙에 얹어준다.
    for (int i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
    }

    // 힙에서 가장 가중치가 낮은 2개 추출 후 트리 형성. 해당 원소를 다시 힙에 넣어준다.
    for (int i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d+%d->%d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }
    e = delete_min_heap(heap);
    print_codes(e.ptree, codes, top);
    clear_tree(e.ptree);
    free(heap);
}

int main(void) {
    char ch_list[] = {'s', 'i', 'n', 't', 'e'};
    int freq[] = {4, 6, 8, 12, 15};

    huffman_tree(freq, ch_list, 5);
    return 0;
}