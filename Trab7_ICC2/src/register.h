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

typedef struct registerKey_t {
	type_t	key_type;
	int		key_size;
	value_t *key_value;
	struct registerKey_t *nextKey;
} registerKey_t;

typedef struct registerField_t {
	type_t	field_type;
	int		field_size;
	value_t *field_value;
	struct registerField_t *nextField;

} registerField_t;

typedef struct registerOffset_t {
	value_t	field_value;
	type_t field_type;
	int	offset;
} registerOffset_t;

/**
 * Conjunto completo de key e Fields
 * Metadata -> definicao: dado que descreve um dado
 */
typedef struct reg_t {
	registerField_t *head_registerField;
	registerField_t *last_registerField;
	registerKey_t *registerKey;
	int numOfFields;
	int sizeofFields;
} reg_t;

void scanKey(metadata_t metadata, reg_t *reg, char *line, char **saveptr);

void saveKey(reg_t* reg, FILE *registerFile);

/**
 * Imprime na Console
 */
void printRegister (FILE *registerFile, metadata_t metadata, int offset);

/**
 * Salva no arquivo
 */
void saveRegister(reg_t* reg, FILE *registerFile);

/**
 * Le da Console
 */
void scanRegister(metadata_t metadata, reg_t* reg, char *line, char **saveptr);

/**
 * Le todos offsets de acordo com o campo
 */
registerOffset_t* fullScanRegister(char *field_name);

#endif /* REGISTER_H_ */
