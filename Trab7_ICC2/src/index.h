/*
 * key.h
 *
 *  Created on: Nov 13, 2014
 *      Author: rafaelbiffineto
 */

#ifndef KEY_H_
#define KEY_H_

#include "metadata.h"
#include "register.h"

typedef struct registerKey_t {
	char	*key_name;
	type_t	key_type;
	int		key_size;
	value_t *key_value;
	struct registerKey_t *nextKey;
} registerKey_t;


//void scanKey(metadata_t metadata, reg_t reg, char *line);

#endif /* KEY_H_ */
