/*
 ============================================================================
 Name        : StructDinamica.c
 Author      : Rafael Biffi Neto
 N. Usp		 : 8937163
 Version     :
 Description : Trabalho 7 - ICC2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadata.h"
#include "register.h"
#include "key.h"

//TYPE ---- type_t
//value_t


void print_value_t(value_t value, type_t type, int size) {
	switch(type) {
	case(INT) : printf("%d", value.i); break;
	case(DOUBLE) : printf("%lf", value.d); break;
	case(CHAR) : printf("%c", value.c); break;
	case(STRING) : printf("%s", value.s); break;
	case(FLOAT) : printf("%f", value.f); break;
	case(ERROR) : printf ("Nao entendeu o tipo\n");
	}
}

type_t verificaTipo(char *str) {
	type_t result;
	if ( strstr(str, "char") != NULL ) {
		result = STRING;

	} else if ( strstr(str, "int") != NULL ) {
		result = INT;

	} else if ( strstr(str, "double") != NULL ) {
		result = DOUBLE;

	} else if ( strstr(str, "float") != NULL) {
		result = FLOAT;

	} else if ( strstr(str, "char") != NULL) {
		result = CHAR;

	} else {
		result = ERROR;

	}
	return result;
}

void Insert (metadata_t* metadata, char *line) {
	reg_t reg;
	FILE *regFile;
	regFile = fopen (metadata->registersFileName, "r");
//	scanKey (*metadata, reg, line);
	reg = scanRegister(*metadata, line);
	saveRegister (reg, regFile);
}


/**
 * Especifica o formato
 * que sera usado no scan para ler o valor
 */
const char *defineScanFormat(type_t type) {
	char *format = malloc (sizeof(char)*5);
	switch (type) {
	case INT: strcpy(format, "%d"); break;
	case DOUBLE: strcpy(format, "%f"); break;
	case STRING: strcpy(format, "%s"); break;
	case FLOAT: strcpy(format, "%f"); break;
	case CHAR: strcpy(format, "%c"); break;
	case ERROR: break;
	}
	printf("format: %s\n", format);
	return format;
}

value_t *defineKey(metadata_t metadata) {
	value_t *key = (value_t*) malloc (metadata.metadataKey.sizeOfKey);

	printf("format: %s\n", defineScanFormat(metadata.metadataKey.key_type));
	scanf(defineScanFormat(metadata.metadataKey.key_type), key);

	printf("\n");
	print_value_t(*key, metadata.metadataKey.key_type, metadata.metadataKey.sizeOfKey);
	//deve ser feita no arquivo

	return key;
}

FILE* Index (metadata_t metadata, char *line) {
	FILE *idx;

	idx = fopen (metadata.registersFileName, "wb");

	//tera que imprimir ordenado! TODO
	//http://support.microsoft.com/kb/73853/en-us
	fwrite (metadata.metadataKey.key_name, metadata.metadataKey.sizeOfKey, 1, idx);	//print key
	fwrite (&metadata.sizeofFields, sizeof(int), 1, idx);							//print offset

	fclose (idx);

	return idx;
}

void printRegisterField (FILE* arq, metadata_t metadata, int offset) {
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


int Search (FILE* idx, FILE *reg, metadata_t metadata, int search) {
	int key, offset, trash;
	idx = fopen (metadata.registersFileName, "rb");
	reg = fopen (metadata.registersFileName, "r");

	while (fscanf (idx, "%d", &key) != EOF) {
		if (key == search) {
			fscanf (idx, "%d", &offset);
			printRegisterField (reg, metadata, offset);
			return 1;
		} else {
			fscanf (idx, "%d", &trash); //joga fora (pula) o offset
		}
	}
	return 0;
}

int main(void) {
	char regName[20];
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	scanf ("%s", regName);
	printf ("%s\n", regName);

	metadata_t metadata = buildMetadata (regName);
	printf("SizeofFields: %d\n", metadata.sizeofFields);
	printf("key_name: %s\n", metadata.metadataKey.key_name);
	printf("sizeOfKey: %d\n", metadata.metadataKey.sizeOfKey);

	read = getline(&line, &len, stdin);

	while ((read = getline(&line, &len, stdin)) != -1) {
//		printf("Retrieved line of length %zu :\n", read);
		printf("%s\n", line);

		if (strstr(line, "insert") != NULL)
			Insert(&metadata, line);
		else if (strstr(line, "index") != NULL)
			Index (metadata, line);
		else if (strstr(line, "search") != NULL) {
//			Search (idx, reg, metadata, search);
		}
		else if (strstr (line, "exit") != NULL)
				return 0;
		 else
			printf("invalid command: %s", line);
	}


	return EXIT_SUCCESS;
}
