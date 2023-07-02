#pragma once

#include "stack.h"

#include "BijectiveMappingConst.h"


typedef uint32_t internal;

typedef struct HashContext
{
    internal hash = 0;
    internal buffer_hash;
    internal iterator = 0;

    internal j_index = 0;
    internal i_index__ = 0;
}GHC;


extern void hash_state_of_cr(Stack* stack, GHC* ghc, size_t index);

extern void hash_state_of_encr(Stack* stack, GHC* ghc, size_t index);

extern void hash_xor_key(Stack* stack, GHC* ghc, size_t index);

extern void merge_state_key_cr(Stack* stack, Stack* stack2, GHC* ghc, size_t index);

extern void merge_state_key_encr(Stack* stack, Stack* stack2, GHC* ghc, size_t index);

extern void hash_key(Stack* stack, GHC* ghc, size_t index);

static void update__(GHC* ghc, Stack* stack_st, size_t index);

extern int32_t gray_encode(int32_t a);

extern int gray_dencode(int a);
