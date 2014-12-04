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
	FILE* idx;
	int createValue = 1;

	idx = fopen (indexName, "w+");
	if (idx != NULL) {
		fwrite(&createValue, 4, 1, idx);
		createValue = 0;
		fwrite(&createValue, 4, 1, idx);

		return idx;
	}

	return NULL;
}

FILE* existIndexFile(char *indexName) {
	FILE *idx;

	idx = fopen (indexName, "r+");
	if (idx != NULL) {
		printf ("File already exists\n");
		return idx;
	}

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
	FILE *idx;

	if ((idx = existIndexFile(indexName)) == NULL) {
		idx = createIndexFile(indexName);
	}
	if (idx != NULL) {
		fwrite(&offsets->field_value, offsets->field_type, /*NUM OF OFFSETS*/ 1, idx);
		//TODO
		fclose(idx);
		return 1;
	}
	return 0;
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
