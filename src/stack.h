#pragma once

#ifndef LIB_STACK_H
#define LIB_STACK_H

#include <iostream>

#include "type.h"

typedef struct Stack Stack;

extern Stack* new_stack(size_t size, vtype_t value);

extern size_t size_stack(Stack* stack);

extern void free_stack(Stack* stack);

extern void set_stack(Stack* stack, size_t index, void* value);

extern void push_stack(Stack* stack, void* value);

extern value_t get_stack(Stack* stack, size_t index);

extern value_t pop_stack(Stack* stack);

static void insert_stack(Stack* stack, size_t index, void* value);

extern void* get_arr(Stack* stack);

#endif