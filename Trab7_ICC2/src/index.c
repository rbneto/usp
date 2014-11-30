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


// Acrescenta campos de Key em seus respectivos registros
void append_registerKey(reg_t *reg, value_t value) {

	registerKey_t *newKey;

	newKey = (registerKey_t*) malloc (sizeof(registerKey_t)*1);

	reg->registerKey = newKey;
	newKey->key_value = &value;

}

// Baseado no metadata, le a Key de cada registro
void scanKey(metadata_t metadata, struct reg_t *reg, char *line) {
	char *token;
	value_t currentValue;

	// joga fora o comando
	token = strtok(line, ",");
	sscanf(token, "%d", (int*) &currentValue);
	append_registerKey(reg, currentValue);

}

// Le um registro do arquivo com base em sua Key
reg_t fscanKey(FILE *registerFile, int key) {
	reg_t result;
	return result;

}

// Salva um registro no arquivo
void saveKey(reg_t reg, FILE *registerFile) {
	registerField_t *aux;

	aux = reg.head_registerField;
	while (aux->nextField != NULL) {
		aux = aux->nextField;
		fwrite (&aux->field_value, 1, aux->field_size, registerFile);
	}
}

FILE* createIndexFile(char *indexName) {
	return NULL;
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
