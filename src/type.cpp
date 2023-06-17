#include "type.h"

extern void* integer(int32_t x)
{
	return (void*)(intptr_t)x;
}

extern void* string(uint8_t x)
{
	return (void*)x;
}