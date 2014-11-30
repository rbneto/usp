/*
 * BSTree.c
 *
 *  Created on: Nov 14, 2014
 *      Author: rafaelbiffineto
 */
#include <stdlib.h>
#include "BSTree.h"

#define LEFT_CHILD 0
#define RIGHT_CHILD 1

#define max(a, b) ((a > b) ? a : b)

BSTree *createBSTree() {
	BSTree *tree;
	tree = (BSTree*) malloc (sizeof(BSTree));

	return tree;
}

int height(Node* root) {
  if (root == NULL) {
    return -1;
  } else {
    return root->height;
  }
}

Node *rodar_esquerda(Node *a) {
  Node *b = a->rightChild;
  a->rightChild = b->leftChild;
  b->leftChild = a;

  a->height = max(height(a->leftChild), height(a->rightChild)) + 1;
  b->height = max(height(b->rightChild), a->height) + 1;

  return b;
}

Node *rodar_direita(Node *a) {
  Node *b = a->leftChild;
  a->leftChild = b->rightChild;
  b->rightChild = a;

  a->height = max(height(a->leftChild), height(a->rightChild)) + 1;
  b->height = max(height(b->leftChild), a->height) + 1;

  return b;
}

Node *rodar_esquerda_direita(Node *a) {
  a->leftChild = rodar_esquerda(a->leftChild);
  return rodar_direita(a);
}

Node *rodar_direita_esquerda(Node *a) {
  a->rightChild = rodar_direita(a->rightChild);
  return rodar_esquerda(a);
}


Node *insert_avl_aux(Node *root, ITEM *item) {
	if (root == NULL) {
		Node *newNode = (Node*) malloc (sizeof(Node));
		newNode->item = item;
		root = newNode;
	} else if (item->value > root->item->value) {
		root->rightChild = insert_avl_aux(root->rightChild, item);
		if (height(root->leftChild) - height(root->rightChild) == -2) {
			if (item->value > root->rightChild->item->value) {
				root = rodar_esquerda(root);
			} else {
				root = rodar_direita_esquerda(root);
			}
		}
	} else if (item->value < root->item->value) {
		root->leftChild = insert_avl_aux(root->leftChild, item);
		if (height(root->leftChild) - height(root->rightChild) == 2) {
			if (item->value < root->leftChild->item->value) {
				root = rodar_direita(root);
			} else {
				root = rodar_esquerda_direita(root);
			}
		}
	}
	root->height = max(height(root->leftChild), height(root->rightChild)) + 1;

  return root;
}

int insert_avl(BSTree *tree, ITEM *item) {
  return (tree->root = insert_avl_aux(tree->root, item)) != NULL;
}

Node *insert_child (int child, Node *node, Node *newNode) {

  if (newNode != NULL) {
    newNode->rightChild = NULL;
    newNode->leftChild = NULL;

    if (child == LEFT_CHILD) {
      node->leftChild = newNode;
    } else {
      node->rightChild = newNode;
    }
  }

  return newNode;
}

int insert_aux (Node *root, Node* newNode) {
	if (root->item->value > newNode->item->value) {
		if (root->leftChild != NULL) {
			return insert_aux(root->leftChild, newNode);
		} else {
			return (insert_child(LEFT_CHILD, root, newNode) != NULL);
		}
	} else if (root->item->value < newNode->item->value) {
		if (root->rightChild != NULL) {
			return insert_aux (root->rightChild, newNode);
		} else {
			 return (insert_child(RIGHT_CHILD, root, newNode) != NULL);
		}
	} else {
		return 0;
	}
}


Node* insert_bstree(BSTree *t, int value) {
	Node *newNode = t->root;

	newNode = (Node*) malloc (sizeof(Node));
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->item->value = value;

	if (t->root == NULL) {
		t->root = newNode;
	} else {
		insert_aux (t->root, newNode);
	}
	return newNode;

}

int search_aux (Node *root, int value, int height) {
	height++;
	if (root == NULL) {
		return -1;
	} else {
		if (root->item->value > value) {
			return search_aux(root->leftChild, value, height);
		} else if (root->item->value < value) {
			return search_aux (root->rightChild, value, height);
		} else {
			return height;
		}
	}
}

int search(BSTree *t, int value) {
	int height = -1;
	if (search_aux (t->root, value, height) == -1) {
		return -1;
	}
	return search_aux (t->root, value, height);
}

void breadthPrint(BSTree *t) {

}

void freeBSTree(BSTree *t) {

}
