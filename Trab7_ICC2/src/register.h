/*
 * register.h
 *
 *  Created on: Nov 12, 2014
 *      Author: rafaelbiffineto
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include "index.h"
#include "metadata.h"
#include <stdio.h>

typedef struct registerField_t {
	char	*field_name;
	type_t	field_type;
	int		field_size;
	value_t *field_value;
	struct registerField_t *nextField;

} registerField_t;

typedef struct registerOffset_t {
	value_t	field_value;
	int	offset;
} registerOffset_t;

/**
 * Conjunto completo de key e Fields
 * Metadata -> definicao: dado que descreve um dado
 */
typedef struct register_t {
	registerField_t *head_registerField;
	registerField_t *last_registerField;
	registerKey_t *registerKey;
	int numOfFields;
	int sizeofFields;
} reg_t;

void scanKey(metadata_t metadata, reg_t *reg, char *line);

void saveKey(reg_t* reg, FILE *registerFile);

/**
 * Imprime na Console
 */
void printRegister (FILE* arq, metadata_t metadata, int offset);

/**
 * Salva no arquivo
 */
void saveRegister(reg_t* reg, FILE *registerFile);

/**
 * Le da Console
 */
void scanRegister(metadata_t metadata, reg_t* reg, char *line);

/**
 * Le todos offsets de acordo com o campo
 */
registerOffset_t* fullScanRegister(char *field_name);

#endif /* REGISTER_H_ */
