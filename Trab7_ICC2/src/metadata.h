/*
 * metadata.h
 *
 *  Created on: Nov 11, 2014
 *      Author: rafaelbiffineto
 */

#ifndef METADATA_H_
#define METADATA_H_

typedef enum type_t { INT, DOUBLE, CHAR, STRING, FLOAT, ERROR } type_t;

/**
 * Descreve uma Key
 * Metadata -> definicao: dado que descreve um dado
 */
typedef struct metadataKey_t {
	char	*key_name;
	type_t 	key_type;
	int		sizeOfKey;
} metadataKey_t;

/**
 * Descreve um Field
 * Metadata -> definicao: dado que descreve um dado
 */

typedef struct metadataField_t {
	char	*field_name;
	type_t	field_type;
	int		field_size;
	struct metadataField_t *nextField;

} metadataField_t;

/**
 * Conjunto completo de key e Fields
 * Metadata -> definicao: dado que descreve um dado
 */
typedef struct metadata_t {
	char *registersFileName;
	metadataKey_t metadataKey;
	metadataField_t *head_metadataField;
	metadataField_t *last_metadataField;
	int sizeofFields;
} metadata_t;

/**
 * Cria um tipo para receber valor seja algum dos abaixo
 */
typedef union value_t {
	int i;
	double d;
	char *s;
	float f;
	char c;
} value_t;


metadata_t buildMetadata(char *fileName);
const char *getTypeScanFormat(type_t type);


#endif /* METADATA_H_ */
