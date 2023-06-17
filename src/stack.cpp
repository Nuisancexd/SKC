#include "stack.h"

typedef struct Stack
{
	vtype_t value;
	value_t* buffer;
	size_t size;
	size_t index;
} Stack;

value_t get_stack(Stack* stack, size_t index);
static void _insert_stack_(Stack* stack, size_t index, void* value);

Stack* new_stack(size_t size, vtype_t value)
{
	switch (value)
	{
	case INTEGER_TYPE:
		break;
	case STRING_TYPE:
		break;
	default:
		std::cout << stderr << "value type not found";
		return NULL;
	}
	Stack* stack = new Stack[sizeof(Stack)];
	stack->buffer = new value_t[size];
	stack->value = value;
	stack->size = size;
	stack->index = 0;
	return stack;
}

void free_stack(Stack* stack)
{
	delete[](stack->buffer);
	delete(stack);
}

void set_stack(Stack* stack, size_t index, void* value)
{
	insert_stack(stack, index, value);
}

void push_stack(Stack* stack, void* value)
{
	insert_stack(stack, stack->index, value);
	stack->index++;
}

value_t get_stack(Stack* stack, size_t index)
{
	if (index >= stack->size)
	{
		std::cout << "overflow size of stack" << std::endl;
		value_t none =
		{
			none.integer = 0,
		};
		return none;
	}
	return stack->buffer[index];
}

value_t pop_stack(Stack* stack)
{
	if (stack->index == 0)
	{
		std::cout << "empty size of stack" << std::endl;
		value_t none =
		{
			none.integer = 0,
		};
		return none;
	}
	
	stack->index--;
	return stack->buffer[stack->index];
}

static void insert_stack(Stack* stack, size_t index, void* value)
{
	if (index > stack->size)
	{
		std::cout << "overflow size of stack  ~ " << stack->index << std::endl;
		return;
	}
	switch (stack->value)
	{
	case INTEGER_TYPE:
		stack->buffer[index].integer = (int32_t)(intptr_t)value;
		break;
	case STRING_TYPE:
	{
		stack->buffer[index].string = (uint8_t)value;
		break;
	}
	default:;
	}
}

void* get_arr(Stack* stack)
{	 
	switch (stack->value)
	{
	case STRING_TYPE:
	{
		uint8_t* str_arr = new uint8_t[stack->index];
		for (size_t i = 0; i < stack->index; ++i)
		{
			str_arr[i] = stack->buffer[i].string;
		}
		return str_arr;		
	}
	case INTEGER_TYPE:
	{
		int32_t* int_arr = new int32_t[stack->index];
		for (size_t i = 0; i < stack->index; ++i)
		{
			int_arr[i] = stack->buffer[i].integer;			
		}		
		return int_arr;
	}
	default:;
	}
}

size_t size_stack(Stack* stack)
{
	return stack->index;
}
