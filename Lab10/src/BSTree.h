#ifndef BSTREE_H
#define BSTREE_H

typedef struct item {
	int value;
} ITEM;

typedef struct node {
	ITEM *item;
	int height;
	struct node *leftChild;
	struct node *rightChild;
} Node;

typedef struct bstree {
	Node *root;
} BSTree;

BSTree *createBSTree();

Node* insert_bstree(BSTree *t, int value);
int insert_avl(BSTree *tree, ITEM *item);
int search(BSTree *t, int value);

void breadthPrint(BSTree *t);
	//imprimir

void freeBSTree(BSTree *t);

#endif
