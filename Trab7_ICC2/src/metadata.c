/*
 * metadata.c
 *
 *  Created on: Nov 11, 2014
 *      Author: rafaelbiffineto
 */

#include "metadata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char KEYWORD_INT[] = "int";
static const char KEYWORD_DOUBLE[] = "double";
static const char KEYWORD_STRING[] = "char[";
static const char KEYWORD_FLOAT[] = "float";
static const char KEYWORD_CHAR[] = "char";

static const char FILENAME[] = "filename";
static const char KEY_NAME[] = "key-name";
static const char KEY_TYPE[] = "key-type";
static const char FIELD_NAME[] = "field-name";
static const char FIELD_TYPE[] = "field-type";


type_t checkType(char *str) {
	type_t result;
	if ( strstr(str, KEYWORD_STRING) != NULL ) {
		result = STRING;
		printf ("TYPE STRING\n");

	} else if ( strstr(str, KEYWORD_INT) != NULL ) {
		result = INT;
		printf ("TYPE INT\n");

	} else if ( strstr(str, KEYWORD_DOUBLE) != NULL ) {
		result = DOUBLE;
		printf ("TYPE DOUBLE\n");

	} else if ( strstr(str, KEYWORD_FLOAT) != NULL) {
		result = FLOAT;
		printf ("TYPE FLOAT\n");

	} else if ( strstr(str, KEYWORD_CHAR) != NULL) {
		result = CHAR;
		printf ("TYPE CHAR\n");


	} else {
		result = ERROR;

	}
	return result;
}

const char *getTypeScanFormat(type_t type) {
	switch(type) {
		case (INT): return "%d";
		case (DOUBLE): return "%lf";
		case (CHAR): return "%c";
		case (STRING): return "%s";
		case (FLOAT): return "%f";
		case (ERROR): return NULL;
 	}
}

int checkSize(char *str) {
	int tamanho;
	type_t type = checkType(str);
	switch(type) {
	case (STRING): {
		char *aux;
		aux = strtok (str,"[");
		while (aux != NULL)
		{
			printf ("%s\n",aux);
			if (sscanf(aux, "%d", &tamanho) != EOF)
//			printf ("Pegou tamanho: %d\n", tamanho);
			aux = strtok (NULL, "]");
		}
		return (sizeof(char) * tamanho); break;
	}
	case (INT):
			return sizeof(int);
	case(DOUBLE):
			return sizeof(double);
	case(CHAR):
			return sizeof(char);
	case(FLOAT):
			return sizeof(float);
	case(ERROR):
			printf ("Nao entendeu o tipo: %s\n", str);
	}
	printf ("Nao entendeu o tipo: %s\n", str);
	return 0;
}

//aloca um novo Field
metadataField_t* append_fieldMeta(metadata_t *metadata) {
	metadataField_t *newField;

	newField = (metadataField_t*) malloc (sizeof(metadataField_t)*1);

	metadata->last_metadataField->nextField = newField;
	newField->nextField = NULL;
	metadata->last_metadataField = newField;

	return newField;
}

/**
 * Compoe o metadata, especificando cada um dos Fields
 */
void readMetaLine(metadata_t *metadata, char *line, FILE *metadataFile) {
//	printf ("readMetaLine RUNNING\n");
	char keyword[20], value[20];
	ssize_t read;
	size_t len = 0;
	sscanf(line, "%s %s", keyword, value);

	if (strstr(keyword, FILENAME) != NULL) {
		metadata->registersFileName = value;

	} else if (strstr(keyword, KEY_NAME) != NULL) {
		metadata->metadataKey.key_name = value;

		// le outra linha
		if ( (read = getline(&line, &len, metadataFile)) != -1 ) {
			sscanf(line, "%s %s", keyword, value);
			metadata->metadataKey.key_type = checkType(value);
			metadata->metadataKey.sizeOfKey = checkSize(value);

		} else exit(EXIT_FAILURE);

	} else if (strstr(keyword, FIELD_NAME) != NULL) {
		metadataField_t *metadataField = append_fieldMeta(metadata);
		metadataField->field_name = value;
		line = (char*) malloc (sizeof(char));
		// le outra linha
		if ( (read = getline(&line, &len, metadataFile)) != -1 ) {
			sscanf(line, "%s %s", keyword, value);
			metadataField->field_type = checkType(value);
			metadataField->field_size = checkSize(value);
			metadata->sizeofFields += metadataField->field_size;

		} else exit(EXIT_FAILURE);
	}
//	printf ("readMetaLine SUCESSFUL\n");
}


// Constroi a struct de Metadados e malloca o no cabeca de Fields
metadata_t buildMetadata(char *metadataFileName) {
//	printf ("buildMetadata RUNNING\n");
	metadata_t metadata;
		metadataField_t *head = (metadataField_t*) calloc (1, sizeof(metadataField_t));
		metadata.head_metadataField=head;
		metadata.last_metadataField=head;
		metadata.sizeofFields=0;
		head->nextField=NULL;
	FILE *metadataFile;
	char * line = NULL;
	ssize_t read;
	size_t len = 0;

	metadataFile = fopen(metadataFileName, "r");

	if (metadataFile == NULL) {
		printf ("ERROR READING METADATA");
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, metadataFile)) != -1) {
//		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
		readMetaLine(&metadata, line, metadataFile); // passar o ponteiro do arquivo
	}
//	printf ("buildMetadata SUCESSFUL\n");
	return metadata;
}

