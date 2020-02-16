#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avlTree AVLTREE;

struct avlTree {
    int value;
    int h;
    AVLTREE *right, *left;
};

AVLTREE *createAVLNode(int newValue, AVLTREE *left, AVLTREE *right) {
    AVLTREE *newNode = (AVLTREE*)malloc(sizeof(AVLTREE));
    newNode->left = left;
    newNode->right = right;
    newNode->value = newValue;
    int i;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int h(AVLTREE *node) {
    if (node == NULL) {
        return -1;
    } else {
        return 1 + max(h(node->left), h(node->right));
    }
}

int isBalanced(AVLTREE *node) {
    int bf = h(node->left) - h(node->right);
    return ((-1 <= bf) && (bf <= 1));
}

int balanceFactor(AVLTREE *node) {
    if (node == NULL) {
        return 0;
    } else if ((node->left != NULL) && (node->right != NULL)) {
        return (node->left->h - node->right->h);
    } else if ((node->left != NULL) && (node->right == NULL)) {
        return (1 + node->left->h);
    } else {
        return -node->right->h - 1;
    }
}

AVLTREE *rotateLeft(AVLTREE *node) {
    AVLTREE *subtreeRoot = NULL;
    if (node != NULL && node->right != NULL) {
        subtreeRoot = node->right;
        node->right = subtreeRoot->left;
        subtreeRoot->left = node;
    }
    subtreeRoot->h = h(subtreeRoot);
    node->h = h(node);
    return subtreeRoot;
}

AVLTREE *rotateRight(AVLTREE *node) {
    AVLTREE *subtreeRoot = NULL;
    if (node != NULL && node->left != NULL) {
        subtreeRoot = node->left;
        node->left = subtreeRoot->right;
        subtreeRoot->right = node;
    }
    subtreeRoot->h = h(subtreeRoot);
    node->h = h(node);
    return subtreeRoot;
}

void print_AVL(AVLTREE *node)
{
	printf(" (");
	if(node == NULL){
		printf(") ");
		return;
	}
	printf(" %d ", node->value);
	print_AVL(node->left);
	print_AVL(node->right);
	printf(") ");
}

AVLTREE *add(AVLTREE *node, int newValue, AVLTREE *root, int *flag) {
    if (node == NULL) {
        node = createAVLNode(newValue, NULL, NULL);
        return node;
    } else if (node->value > newValue) {
        node->left = add(node->left, newValue, root, flag);
    } else {
        node->right = add(node->right, newValue, root, flag);
    }

    node->h = h(node);
    AVLTREE *child;
    if (balanceFactor(node) == 2 || balanceFactor(node) == -2) {
        printf("Antes de ajustar balanceamento...\n  ");
        print_AVL(root);
        printf("\n");
        *flag = 0;
        if (balanceFactor(node) == 2) {
            child = node->left;
            if (balanceFactor(child) == -1) {
                node->left = rotateLeft(child);
            }
            node = rotateRight(node);
        } else if (balanceFactor(node) == -2) {
            child = node->right;
            if (balanceFactor(child) == 1) {
                node->right = rotateRight(child);
            }
            node = rotateLeft(node);
        }
    }
    return node;
}

int main() {
    int num, i = 0, arr[1000000];
    AVLTREE *root = NULL;
    while (scanf("%d", &arr[i++]) != EOF);
    int j;
    for (j = 0; j < i - 1; ++j) {
        printf("----\n");
        int flag = 1;
        printf("Adicionando %d\n", arr[j]);
        root = add(root, arr[j], root, &flag);
        if (flag) {
            printf("Continuou AVL...\n  ");
            print_AVL(root);
            printf("\n");
        } else {
            printf("Depois de ajustar balanceamento...\n  ");
            print_AVL(root);
            printf("\n");
        }
    }
    printf("----\n");
    return 0;
}