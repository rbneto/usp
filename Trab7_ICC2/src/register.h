/*
 * register.h
 *
 *  Created on: Nov 12, 2014
 *      Author: rafaelbiffineto
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include "key.h"
#include "metadata.h"
#include <stdio.h>

typedef struct registerField_t {
	char	*field_name;
	type_t	field_type;
	int		field_size;
	value_t *field_value;
	struct registerField_t *nextField;

} registerField_t;

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

void saveRegister(reg_t reg, FILE *registerFile);
reg_t scanRegister(metadata_t metadata, char *line);


#endif /* REGISTER_H_ */
