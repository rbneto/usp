#ifndef NODEQUEUE_H
#define NODEQUEUE_H

#include "BSTree.h"

typedef struct nodequeue  {
	Node *node;
	struct nodequeue *prox;
} NodeQueue;

typedef struct queue  {
	NodeQueue *head;
	NodeQueue *tail;
} Queue;

Queue *createNodeQueue();

void insertNodeQueue(Queue *q);
void breadth_first(Queue *q, Node *root);
	void push (Queue *q, Node *new);


int emptyNodeQueue(Queue *);

NodeQueue *frontNodeQueue(Queue *q);
Node* popNodeQueue(Queue *q);

void printNodeQueue (Queue *q);


void freeNodeQueue(Queue *q);

#endif
