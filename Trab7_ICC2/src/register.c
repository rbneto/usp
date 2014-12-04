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
void scanKey(metadata_t metadata, reg_t *reg, char *line) {
	char *token;
	char *dismiss = (char*) malloc (sizeof(strlen(line)));
	value_t *currentValue = (value_t*) malloc (sizeof(value_t));

	// joga fora o comando
	token = strtok(line, ",");
	sscanf(token, "%s %d", dismiss, (int*) currentValue);
	reg->registerKey = (registerKey_t*) malloc (sizeof(registerKey_t)*1);
	reg->registerKey->key_value = currentValue;
	reg->registerKey->key_size = sizeof(int);
}

// Le um registro do arquivo com base em sua Key
reg_t fscanKey(FILE *registerFile, int key) {
	reg_t result;
	return result;

}

// Salva um registro no arquivo
void saveKey(reg_t* reg, FILE *registerFile) {

	if (reg->registerKey != NULL) {
		fwrite (&reg->registerKey->key_value, 1, reg->registerKey->key_size, registerFile);
	}
}

void printField(registerField_t *field) {
	switch(field->field_type) {
	case (INT): printf("%d\n", *((int *) field->field_value)); break;
	case (DOUBLE): printf("%lf\n", (double *) field->field_value); break;
	case (CHAR): printf("%c\n", (char) &field->field_value); break;
	case (FLOAT): printf("%f\n", (float *) field->field_value); break;
	case (STRING): printf("%s\n", (char*) field->field_value); break;
	case (ERROR): printf ("ERROR");
	}
}

// Preenche o Field com seu respectivo valor
void scanField(char *token, registerField_t *field) {
	char *copy;
	switch(field->field_type) {
	case (INT): {
		int number;
		while (*token) {
			if (sscanf(token, "%d", &number) == 1) {
				break;
			}
			token++;
		}
		//				sscanf(token, "%d", (int*) &(field->field_value));
		field->field_value = (value_t*) &number;
		field->field_size = sizeof(int);
		printf ("FIELD TYPE: INT\nnumber:%d\n", number); break;
	}
	case (DOUBLE): {
		sscanf(token, "%lf", (double*) &(field->field_value));
		field->field_size = sizeof(double);
		printf ("FIELD TYPE: DOUBLE\n"); break;
	}
	case (CHAR):
		sscanf(token, "%c", (char*) &(field->field_value));
		printf ("FIELD TYPE: CAHR\n");
		break;
	case (FLOAT):
		sscanf(token, "%f", (float*) &(field->field_value));
		printf ("FIELD TYPE: FLOAT\n");
		break;
	case (STRING):
		copy = (char *) malloc (strlen(token));
		strcpy(copy, token);
		field->field_value = (value_t *) copy;
		field->field_size = strlen(token);
		printf ("FIELD TYPE: STRING\n");
		break;
	case (ERROR):
		printf ("ERROR");
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
	scanField(token, newField);
	printField (newField);

}

// Baseado no metadata, cria a struct de registros e chama funcoes para preenche-la
void scanRegister(metadata_t metadata, reg_t* reg, char *line) {
	printf ("scanRegister RUNNING\n");
	char *token;
	registerField_t *head;
	head = (registerField_t*) malloc (sizeof(registerField_t));
	reg->last_registerField = head;
	reg->head_registerField = head;
	head->nextField = NULL;
	metadataField_t *currentMetaField;

	// joga fora o comando
	token = strtok(line, ",");

	currentMetaField = metadata.head_metadataField;
	while (((token = strtok (NULL, ",")) != NULL) && (currentMetaField->nextField != NULL)) {		//espaco nao ta funcionando, tratar aspas e insert 4
		printf ("TOKEN:%s\n", token);
		currentMetaField = currentMetaField->nextField;
		append_registerField(reg, currentMetaField, token);
	}
	printf ("scanRegister SUCCESSFUL\n");
}

// Baseado no metadata, le um registro do arquivo
reg_t fscanRegister(FILE *registerFile, int position) {
	//TODO
}

void printRegister (FILE* arq, metadata_t metadata, int offset) {
	metadataField_t *aux;

	fseek (arq, offset, SEEK_SET);
	fread (stdout, metadata.metadataKey.sizeOfKey, 1, arq);
	printf ("\n");

	aux = metadata.head_metadataField;
	while (aux->nextField != NULL) {
		aux = aux->nextField;
		fread (stdout, aux->field_size, 1, arq);
		printf ("\n");
	}

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
		fwrite (&aux->field_value, 1, aux->field_size, regFile);
	}
	printf ("scanRegister SUCCESSFUL\n");
}

