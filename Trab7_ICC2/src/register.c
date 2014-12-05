/*
 * register.c
 *
 *  Created on: Nov 12, 2014
 *      Author: rafaelbiffineto
 */

#include "metadata.h"
#include "register.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Baseado no metadata, le a Key de cada registro
void scanKey(metadata_t metadata, reg_t *reg, char *line, char **saveptr) {
	char *token;
	char *dismiss = (char*) malloc (strlen(line));
	char *valueStr = (char *) malloc (strlen(line));

	// joga fora o comando
	token = strtok_r(line, ",", saveptr);
	sscanf(token, "%s %s", dismiss, valueStr);

	reg->registerKey = (registerKey_t*) malloc (sizeof(registerKey_t));
	reg->registerKey->key_value = (value_t*) malloc (sizeof(value_t));

	switch(reg->registerKey->key_type) {
	case (INT): sscanf(valueStr, "%d", &reg->registerKey->key_value->i); reg->registerKey->key_size = sizeof(int); break;
	case (DOUBLE): sscanf(valueStr, "%lf", &reg->registerKey->key_value->d); break;
	case (CHAR): sscanf(valueStr, "%c", &reg->registerKey->key_value->c); break;
	case (FLOAT): sscanf(valueStr, "%f", &reg->registerKey->key_value->f); break;
	case (STRING): reg->registerKey->key_value->s = (char*) malloc (strlen(valueStr)); strcpy(reg->registerKey->key_value->s, valueStr); break;
	case (ERROR): printf ("ERROR");
	}

}

// Le um registro do arquivo com base em sua Key
reg_t fscanKey(FILE *registerFile, int key) {
	reg_t result;
	return result;

}

// Salva um registro no arquivo
void saveKey(reg_t* reg, FILE *registerFile) {

	if (reg->registerKey != NULL) {
		switch (reg->registerKey->key_type) {
		case(INT): fwrite (&reg->registerKey->key_value->i, reg->registerKey->key_size, 1, registerFile); break;
		case(DOUBLE): fwrite (&reg->registerKey->key_value->d, reg->registerKey->key_size, 1, registerFile); break;
		case(CHAR): fwrite (&reg->registerKey->key_value->c, reg->registerKey->key_size, 1, registerFile); break;
		case(FLOAT): fwrite (&reg->registerKey->key_value->f, reg->registerKey->key_size, 1, registerFile); break;
		case(STRING): fwrite (reg->registerKey->key_value->s, reg->registerKey->key_size, 1, registerFile); break;
		case(ERROR): break;
		}
	}
}

void printKey(registerKey_t *key) {
	switch(key->key_type) {
	case (INT): printf("%d", *((int *) key->key_value)); break;
	case (DOUBLE): printf("%lf", *((double *) key->key_value)); break;
	case (CHAR): printf("%c", *((char *) key->key_value)); break;
	case (FLOAT): printf("%f", *((float *) key->key_value)); break;
	case (STRING): printf("%s", (char*) key->key_value); break;
	case (ERROR): printf ("ERROR");
	}
}


void printField(registerField_t *field) {
	switch(field->field_type) {
	case (INT): printf(" %d", field->field_value->i); break;
	case (DOUBLE): printf(" %.2f", field->field_value->d); break;
	case (CHAR): printf(" %c", field->field_value->c); break;
	case (FLOAT): printf(" %.2f", field->field_value->f); break;
	case (STRING): printf("%s", (char*) field->field_value); break;
	case (ERROR): printf ("ERROR");
	}
}

// Preenche o Field com seu respectivo valor
void scanField(char *token, registerField_t *field) {
	char *copy;
	switch(field->field_type) {
	case (INT): sscanf(token, "%d", &field->field_value->i); break;
	case (DOUBLE): sscanf(token, "%lf", &field->field_value->d); break;
	case (CHAR): sscanf(token, "%c", &field->field_value->c); break;
	case (FLOAT): sscanf(token, "%f", &field->field_value->f); break;
	case (STRING): field->field_value->s = (char*) malloc (strlen(token)); strcpy(field->field_value->s, token); break;
	case (ERROR): printf ("ERROR");
	}
}

// Malloca um novo campo Field para ser preenchido
void append_registerField(reg_t *reg, metadataField_t *metadataField, char *token) {

	registerField_t *newField;

	newField = (registerField_t*) malloc (sizeof(registerField_t)*1);

	reg->last_registerField->nextField = newField;
	newField->nextField = NULL;
	reg->last_registerField = newField;
	newField->field_type = metadataField->field_type;
	newField->field_size = metadataField->field_size;
	newField->field_value = (value_t*) malloc (sizeof(value_t));
	scanField(token, newField);
	printField (newField);

}

// Baseado no metadata, cria a struct de registros e chama funcoes para preenche-la
void scanRegister(metadata_t metadata, reg_t* reg, char *line, char **saveptr) {
	printf ("scanRegister RUNNING\n");
	char *token = malloc(sizeof(strlen(line)));
	registerField_t *head;
	head = (registerField_t*) malloc (sizeof(registerField_t));
	reg->last_registerField = head;
	reg->head_registerField = head;
	head->nextField = NULL;
	metadataField_t *currentMetaField;

	currentMetaField = metadata.head_metadataField;
	while (((token = strtok_r (NULL, ",", saveptr)) != NULL) && (currentMetaField->nextField != NULL)) {		//espaco nao ta funcionando, tratar aspas e insert 4
		printf ("TOKEN:%s\n", token);
		currentMetaField = currentMetaField->nextField;
		append_registerField(reg, currentMetaField, token);
	}
	printf ("scanRegister SUCCESSFUL\n");
}

// Baseado no metadata, le um registro do arquivo
reg_t fscanRegister(FILE *registerFile, metadata_t metadata, int position) {
}

void printRegister (FILE *registerFile, metadata_t metadata, int offset) {
	metadataField_t *aux;
	registerKey_t *key = (registerKey_t *) malloc (sizeof(registerKey_t));
	registerField_t	*field = (registerField_t *) malloc (sizeof(registerField_t));
	int count = 0;
	void *buffer = malloc (metadata.sizeOfRegister);

	key->key_type = metadata.metadataKey.key_type;
	key->key_value = malloc (sizeof(metadata.metadataKey.sizeOfKey));
	count = fseek(registerFile, offset, SEEK_SET);
	count = fread(key->key_value, metadata.metadataKey.sizeOfKey, 1, registerFile);
	printKey(key);

	aux = metadata.head_metadataField;
	while (aux->nextField != NULL) {
		aux = aux->nextField;
		field->field_type = aux->field_type;
		field->field_value = malloc (sizeof(aux->field_size));
		fread(field->field_value, aux->field_size, 1, registerFile);
		printField(field);
	}
	printf("\n");
}


/**
 * salva o register no arquivo
 */
void saveRegister(reg_t* reg, FILE *regFile) {
	printf ("saveRegister RUNNING\n");
	registerField_t *aux;

	aux = reg->head_registerField;
	while (aux->nextField != NULL) {
		aux = aux->nextField;
		switch (aux->field_type) {
		case(INT): fwrite (&aux->field_value->i, aux->field_size, 1, regFile); break;
		case(DOUBLE): fwrite (&aux->field_value->d, aux->field_size, 1, regFile); break;
		case(CHAR): fwrite (&aux->field_value->c, aux->field_size, 1, regFile); break;
		case(FLOAT): fwrite (&aux->field_value->f, aux->field_size, 1, regFile); break;
		case(STRING): fwrite (aux->field_value->s, aux->field_size, 1, regFile); break;
		case(ERROR): break;
		}
	}
	fflush(regFile);
	printf ("scanRegister SUCCESSFUL\n");
}

