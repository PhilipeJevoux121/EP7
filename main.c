#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(char inOrder[], char preOrder[], int inStart, int inEnd, int* preIndex, int map[]) {
    if (inStart > inEnd) {
        return NULL;
    }

    Node* newNode = createNode(preOrder[(*preIndex)++]);

    if (inStart == inEnd) {
        return newNode;
    }

    int inIndex = map[newNode->data];

    newNode->left = buildTree(inOrder, preOrder, inStart, inIndex - 1, preIndex, map);
    newNode->right = buildTree(inOrder, preOrder, inIndex + 1, inEnd, preIndex, map);

    return newNode;
}

void postOrderTraversal(Node* root, char result[], int* index) {
    if (root == NULL) {
        return;
    }

    postOrderTraversal(root->left, result, index);
    postOrderTraversal(root->right, result, index);
    result[(*index)++] = root->data;
}

int main() {
    int numCases;
    scanf("%d", &numCases);

    char preOrder[53];
    char inOrder[53];
    char result[53];

    while (numCases--) {
        int numNodes;
        scanf("%d", &numNodes);

        scanf("%s %s", preOrder, inOrder);

        int map[256] = {0}; // Mapeamento de caractere para índice
        for (int i = 0; i < numNodes; i++) {
            map[inOrder[i]] = i;
        }

        int preIndex = 0;
        Node* root = buildTree(inOrder, preOrder, 0, numNodes - 1, &preIndex, map);

        int index = 0;
        postOrderTraversal(root, result, &index);
        result[numNodes] = '\0'; // Adiciona o caractere nulo para finalizar a string

        printf("%s\n", result);

        free(root);
    }

    return 0;
}