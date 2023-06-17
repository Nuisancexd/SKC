
#ifndef _TYPE_H
#define _TYPE_H

#include <cstdint>



typedef enum vtype_t
{
	INTEGER_TYPE,
	STRING_TYPE,
} vtype_t;

typedef union value_t
{
	int32_t integer;
	uint8_t string;
} value_t;


extern void* integer(int32_t x);
extern void* string(uint8_t x);

#endif