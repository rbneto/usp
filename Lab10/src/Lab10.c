/*
 ============================================================================
 Name        : Lab10.c
 Author      : Rafael Biffi Neto
 N. Usp		 : 8937163
 Description : Arvore Binaria - Arvore AVL
 Fonte Aux	 : Slides Alg1 - Prof. Paulovich
 ============================================================================
 */

// usei o mesmo arquivo do lab10, portanto algumas funcoes alheias ao lab12 ainda estao presentes

#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"
#include "NodeQueue.h"


int main(void) {
	int insertValue, searchValue;
	int i, height, numOfElements;
	Node *newNode;
	Node *insertQueue;
	NodeQueue *aux;
	BSTree* t;
	Queue *q;
	ITEM *item;


//	scanf ("%d", &numOfElements);

	t = createBSTree();
	q = createNodeQueue();

	while (scanf ("%d", &insertValue) != EOF) {
//	for (i=0; i<10; i++) {
//		scanf ("%d", &insertValue);
		item = (ITEM*) malloc (sizeof(ITEM));
		item->value = insertValue;
		insert_avl(t,item);
	}

	breadth_first (q, t->root);


	printNodeQueue(q);

//	while (aux != NULL) {
//		if (aux->node->item != NULL)
//			printf ("%d ", aux->node->item->value);
//		aux = aux->prox;
//	}

//	while (scanf ("%d", &searchValue) != EOF) {
//		if ((height = search(t, searchValue)) != -1) {
//			printf ("ACHOU %d\n", height);
//		} else {
//			printf ("NAO ACHOU\n");
//		}
//	}


	return EXIT_SUCCESS;
}
