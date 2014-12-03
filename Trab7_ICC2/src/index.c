/*
 * key.c
 *
 *  Created on: Nov 13, 2014
 *      Author: rafaelbiffineto
 */

#include "metadata.h"
#include "register.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* createIndexFile(char *indexName) {
	FILE* indexFile;

	indexFile = fopen(indexName, "a");
	return indexFile;
}

FILE* existIndexFile(char *indexName) {
	return NULL;

}

/**
 * Ordena estrutura e retorna
 */
registerOffset_t* sortIndex(registerOffset_t* offsets) {
	return offsets;
}

/**
 * Salva estrutura no .idx
 */
int saveIndex(char *indexName, registerOffset_t *offsets) {
	return NULL;
}

/**
 * Le de .idex e retorna estrutura ordenada
 */
registerOffset_t* readIndex(char *indexName) {
	return NULL;
}

/**
 * Busca na estrutura ordernada e retorna offset
 */
int findRegisterOffset(registerOffset_t *offsets, value_t searchWord) {
	return NULL;
}
