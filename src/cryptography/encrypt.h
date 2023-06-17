#pragma once

#include "stack.h"

#include "type.h"

#include "BijectiveMappingConst.h"

extern void hash_state(Stack* stack);

extern void dehash_state(Stack* stack);

extern int32_t gray_encode(int32_t a);

extern int gray_dencode(int a);

extern void Hash_xor_key(Stack* stack);

extern void hash_key(Stack* stack);

extern void dehash_key(Stack* stack);

extern void merge_state_key(Stack* stack, Stack* stack2);