/*
 * register.c
 *
 *  Created on: Nov 12, 2014
 *      Author: rafaelbiffineto
 */

#include "metadata.h"
#include "register.h"
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printField(registerField_t *field) {
	switch(field->field_type) {
		case (INT):
				printf("%d\n", (int) &field->field_value); break;
		case (DOUBLE):
				printf("%lf\n", (double*) &field->field_value); break;
		case (CHAR):
				printf("%c\n", (char) &field->field_value); break;
		case (FLOAT):
				printf("%f\n", (float*) &field->field_value); break;
		case (STRING):
				printf("%s\n", (char*) &field->field_value); break;
		case (ERROR):
				printf ("ERROR");
 	}
}

// Preenche o Field com seu respectivo valor
void scanField(char *token, registerField_t *field) {
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
				printf ("FIELD TYPE: INT\nnumber:%d\n", number); break;
		}
		case (DOUBLE): {
				sscanf(token, "%lf", (double*) &(field->field_value));
				printf ("FIELD TYPE: DOUBLE\n"); break;
		}
		case (CHAR):
				sscanf(token, "%c", (char*) &(field->field_value));
				printf ("FIELD TYPE: CAHR\n"); break;
		case (FLOAT):
				sscanf(token, "%f", (float*) &(field->field_value));
				printf ("FIELD TYPE: FLOAT\n"); break;
		case (STRING):
				sscanf(token, "%s", (char*) &(field->field_value));
				printf ("FIELD TYPE: STRING\n"); break;
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
reg_t scanRegister(metadata_t metadata, char *line) {
	printf ("scanRegister RUNNING\n");
	char *token;
	registerField_t *head;
	head = (registerField_t*) malloc (sizeof(registerField_t));
	reg_t reg;
		reg.last_registerField = head;
		reg.head_registerField = head;
		head->nextField = NULL;
	metadataField_t *currentMetaField;

	// joga fora o comando
	token = strtok(line, ",");

	currentMetaField = metadata.head_metadataField;
	while (((token = strtok (NULL, ",")) != NULL) && (currentMetaField->nextField != NULL)) {		//espaco nao ta funcionando, tratar aspas e insert 4
		printf ("TOKEN:%s\n", token);
		currentMetaField = currentMetaField->nextField;
		append_registerField(&reg, currentMetaField, token);
	}
	printf ("scanRegister SUCCESSFUL\n");
	return reg;
}

// Baseado no metadata, le um registro do arquivo
reg_t fscanRegister(FILE *registerFile, int position) {
	//TODO
}

/**
 * salva o register no arquivo
 */
void saveRegister(reg_t reg, FILE *regFile) {
	printf ("saveRegister RUNNING\n");
	registerField_t *aux;

	aux = reg.head_registerField;
	while (aux->nextField != NULL) {
		aux = aux->nextField;
		fwrite (&aux->field_value, 1, aux->field_size, regFile);
	}
	printf ("scanRegister SUCCESSFUL\n");
}

