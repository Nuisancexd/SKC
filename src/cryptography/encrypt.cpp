#include "encrypt.h"


void hash_state(Stack* stack)
{
    for (int i = size_stack(stack) - 1; i >= 0; --i)
    {
        set_stack(stack, i, string(Pi[get_stack(stack, i).string]));
    }
}

void dehash_state(Stack* stack)
{
    for (size_t i = 0; i < size_stack(stack); ++i)
    {
        uint8_t smb = get_stack(stack, i).string;
        for (size_t j = 0; j < 256; ++j)
        {
            if (smb == Pi[j])
            {
                set_stack(stack, i, string((uint8_t)j));
                break;
            }
        }
    }
}


int32_t gray_encode(int32_t a)
{    
    return a ^ (a >> 1);
}

int gray_dencode(int a)
{
    a = a ^ (a >> 1);
    a = a ^ (a >> 2);
    a = a ^ (a >> 4);

    return a;
}



void Hash_xor_key(Stack* stack)
{
    for (size_t i = 0; i < size_stack(stack); ++i)
    {
        uint32_t vl = get_stack(stack, i).integer ^ A[i];
        set_stack(stack, i, integer(vl));
    }
}


void merge_state_key(Stack* stack, Stack* stack2)
{
    size_t j = 0;
    for (size_t i = 0; i < size_stack(stack); ++i)
    {
        if (size_stack(stack2) == (j + 1))
        {
            j = 0;
        }
        set_stack(stack, i, string(get_stack(stack, i).string ^ get_stack(stack2, j).string));
    }
}


void hash_key(Stack* stack)
{
    for (int i = 0; i < size_stack(stack); ++i)
    {
        for (int j = size_stack(stack) - 1; j >= 0; --j)
        {
            set_stack(stack, i, string(Tau[get_stack(stack, j).string]));
        }
    }
}

void dehash_key(Stack* stack)
{
    for (size_t i = 0; i < size_stack(stack); ++i)
    {
        uint8_t smb = get_stack(stack, i).string;
        for (size_t j = 0; j < 256; ++j)
        {
            if (smb == Tau[j])
            {
                set_stack(stack, i, string((uint8_t)j));
                break;
            }
        }
    }
}