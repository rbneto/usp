/*
 * NodeQueue.c
 *
 *  Created on: Nov 14, 2014
 *      Author: rafaelbiffineto
 */

#include "NodeQueue.h"
#include "stdlib.h"
#include <stdio.h>

Queue *createNodeQueue() {
	Queue* q;
	NodeQueue *head;

	q = (Queue*) malloc (sizeof(Queue));
	head = (NodeQueue*) malloc (sizeof(NodeQueue));
	head->prox= NULL;
	head->node = NULL;
	q->head = head;
	q->tail = head;

	if (q != NULL) {
//		printf ("NOT NULL");
		return q;
	}
	return NULL;
}

void push (Queue *q, Node *new) {
	if (new != NULL) {
		NodeQueue *newNode;
		newNode = (NodeQueue*) malloc (sizeof(NodeQueue));
		newNode->node = new;
		newNode->prox = NULL;
		q->tail->prox = newNode;
		q->tail = q->tail->prox;
//		printf ("push inseriu %d\n", new->value);
	}
}
void breadth_first(Queue *q, Node *root) {
	if (root != NULL) {
		push (q, root);
		insertNodeQueue(q);
	}
}

void printNodeQueue (Queue *q) {
	NodeQueue *aux;
	aux = q->head->prox;
	while (aux != NULL) {
		printf ("%d ", aux->node->item->value);
		aux = aux->prox;
	}
}

void insertNodeQueue(Queue *q) {
	if (q != NULL) {
//		puts ("insertNodeQueue\n");
		Node *new;
		new = popNodeQueue (q);
//		puts ("FLAG");
		push (q, new->leftChild);
		push (q, new->rightChild);
		q->head->prox = q->head->prox->prox;
		if (q->head->prox != NULL) {
			insertNodeQueue (q);
		}

	}
}

int emptyNodeQueue(Queue *q) {
	if (q->tail == q->head) {
		return 1;
	}
	return 0;
}

NodeQueue *frontNodeQueue(Queue *q) {
	//ve quem ta no topo
	return q->head->prox;
}
Node* popNodeQueue(Queue *q) {
	//tira quem ta no topo
	NodeQueue *node;
	if (q->head->prox != NULL) {
	printf ("%d ", q->head->prox->node->item->value);
//	printf ("flag\n");
	if (q->head->prox->node->leftChild !=  NULL || q->head->prox->node->rightChild != NULL) {
		printf ("eh pai de ");
		if (q->head->prox->node->leftChild !=  NULL && q->head->prox->node->rightChild != NULL) {
			printf ("%d e %d\n", q->head->prox->node->leftChild->item->value, q->head->prox->node->rightChild->item->value);
		} else if (q->head->prox->node->leftChild != NULL) {
			printf ("%d\n", q->head->prox->node->leftChild->item->value);
		} else if (q->head->prox->node->rightChild != NULL) {
			printf ("%d\n", q->head->prox->node->rightChild->item->value);
		}
	} else {
		printf ("nao possui filhos\n");
	}
	node = q->head->prox;
	return node->node;
	}
	return NULL;
}

void freeNodeQueue(Queue *q) {
	free (q);
	q = NULL;
}

