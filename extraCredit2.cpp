//
// Created by Patrick on 12/7/2018.
//


typedef struct Node *TREE;

struct Node {
    char* label;
    TREE leftChild, rightChild;
};

TREE tree;

static TREE makeTree(char* input){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    return root;
}

static TREE makeGate(TREE one, TREE two, char* op){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));

    root->leftChild = one;
    root->rightChild = two;
    root->label = op;

    return root;
}

