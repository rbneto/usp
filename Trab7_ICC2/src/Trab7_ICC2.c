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
#include "index.h"

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

/**
 * Insert - Comando do Enunciado
 * 1. L� da console a linha contendo cada campo de metadado
 * 2. Inserir no .reg
 * 3. Mudar o cabecalho de cada .idx para 0
 * 4. Acrescentar o cara no final de cada .idx
 */
void Insert (metadata_t* metadata, char *line) {
	reg_t *reg;
	reg = (reg_t*) malloc (sizeof(reg_t));
	FILE *regFile;
	char *saveptr;

	//checar se arquivo ja nao esta aberto
	regFile = fopen (metadata->registersFileName, "w+");

	scanKey (*metadata, reg, line, &saveptr);
	saveKey (reg, regFile);
	scanRegister(*metadata, reg, line, &saveptr);
	saveRegister (reg, regFile);

	fflush(regFile);
	printRegister(regFile, *metadata, 0);
}

/**
 * Index Comando do Enunciado
 * 1. Verifica e nao encontra o arquivo .idx
 * 1a. Cria o arquivo.
 * 1b. Le tudo o register e ordena em memoria
 * 1c. Salva estrutura no .idx, lembrar do cabecalho com: Alterado S/N e Quantidade Indexada
 * 2. Ja existe o arquivo .idx
 * 2a. Existe arquivo e esta com ordenado volta.
 * 2b. Le arquivo .idx para dentro da estrutura de ordenacao.
 * 2c. Altera o cabecalho.
 * 2d. Sobescreve o arquivo .idx
 */
FILE* IndexField(metadata_t metadata, char *line, char *field) {
	FILE *idx;

	idx = fopen (metadata.registersFileName, "wb");

	//tera que imprimir ordenado! TODO
	//http://support.microsoft.com/kb/73853/en-us
	fwrite (metadata.metadataKey.key_name, metadata.metadataKey.sizeOfKey, 1, idx);	//print key
	fwrite (&metadata.sizeOfRegister, sizeof(int), 1, idx);							//print offset

	fclose (idx);

	return idx;
}

/**
 * Index - Comando do Enunciado
 * Chama IndexField passando como campo a key
 */
FILE* Index (metadata_t metadata, char *line) {
	return IndexField(metadata, line, "key");
}


/**
 * Search - Comando do Enunciado
 * 1. Dado o campo, e nao tem o .idx
 * 1a. Le reg por reg ate encontrar o valor de campo == search
 * 2. Existe o .idx atualizado
 * 2a. Le arquivo .idx para dentro da estrutura de ordenacao.
 * 2b. Encontra o valor de campo == search, por busca binaria
 * 3. Existe o .idx nao atualizado
 * 3a. Chama Index.
 * 3b. Encontra o valor de campo == search, por busca binaria
 * Imprime o reg encontrado.
 */
int SearchField (FILE* idx, FILE *reg, metadata_t metadata, char *field, type_t *searchWord) {
	int key, offset, trash;
	idx = fopen (metadata.registersFileName, "rb");
	reg = fopen (metadata.registersFileName, "r");

	while (fscanf (idx, "%d", &key) != EOF) {
		if (key == searchWord) {
			fscanf (idx, "%d", &offset);
			printRegister (reg, metadata, offset);
			return 1;
		} else {
			fscanf (idx, "%d", &trash); //joga fora (pula) o offset
		}
	}
	return 0;
}

/**
 * Index - Comando do Enunciado
 * Chama IndexField passando como campo a key
 * Retorna o offset
 */
int Search (FILE* idx, FILE *reg, metadata_t metadata, type_t searchWord) {
	return SearchField(idx, reg, metadata, "key", searchWord);
}


FILE* regFile, metadataFile, indexFiles;

int main(void) {
	char regName[20];
	char *line;
	size_t len = 0;
	ssize_t read;

	scanf ("%s", regName);
	printf ("%s\n", regName);

	metadata_t metadata = buildMetadata (regName);
	printf("SizeofFields: %d\n", metadata.sizeOfRegister);
	printf("key_name: %s\n", metadata.metadataKey.key_name);
	printf("sizeOfKey: %d\n", metadata.metadataKey.sizeOfKey);

	read = getline(&line, &len, stdin);

	//Teste de Index
	createIndexFile("teste.idx");

	while ((read = getline(&line, &len, stdin)) != -1) {
		printf("%s\n", line);
		strtok(line, "\n");
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
