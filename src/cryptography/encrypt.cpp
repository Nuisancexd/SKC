#include "encrypt.h"

typedef struct HashContext GHC;

static void update__(GHC* ghc, Stack* stack_st, size_t index)
{
    ghc->iterator == 255 ? ghc->iterator = 0 : ++ghc->iterator;
    ghc->buffer_hash = get_stack(stack_st, index).integer ^ (CUI32[ghc->iterator] ^ ghc->hash);
}

void hash_state_of_cr(Stack* stack, GHC* ghc, size_t index)
{
    update__(ghc, stack, index);
    ghc->hash = Pi[get_stack(stack, index).string] ^ ghc->buffer_hash;
    set_stack(stack, index, string(ghc->hash ^ (ghc->buffer_hash ^ ghc->iterator)));
}

void hash_state_of_encr(Stack* stack, GHC* ghc, size_t index)
{
    update__(ghc, stack, index);
    uint8_t smb = get_stack(stack, index).string;
    ghc->hash = ((internal)smb ^ ghc->buffer_hash) ^ (ghc->buffer_hash ^ ghc->iterator);
    for (size_t j = 0; j < 256; ++j)
    {
        if (ghc->hash == Pi[j])
        {
            set_stack(stack, index, string((uint8_t)j));
            break;
        }
    }
}


void hash_xor_key(Stack* stack, GHC* ghc, size_t index)
{
    internal vl = get_stack(stack, index).integer ^ ((CUL64[index] % CUI32[index]));
    set_stack(stack, index, string(vl));
}

void merge_state_key_cr(Stack* stack, Stack* stack2, GHC* ghc, size_t index)
{
    uint8_t smb_ = (get_stack(stack, index).string >> 32) + (get_stack(stack2, ghc->j_index).string >> 32) - CUI32[ghc->i_index__];
    set_stack(stack, index, string(smb_));                                  
    (ghc->j_index + 1) == size_stack(stack2) ? ghc->j_index = 0 : ++ghc->j_index;
    (ghc->i_index__ + 1) == 255 ? ghc->i_index__ = 0 : ++ghc->i_index__;

}

void merge_state_key_encr(Stack* stack, Stack* stack2, GHC* ghc, size_t index)
{
    uint8_t smb = (get_stack(stack, index).string >> 32) - (get_stack(stack2, ghc->j_index).string >> 32) + CUI32[ghc->i_index__];
    set_stack(stack, index, string(smb));

    (ghc->j_index + 1) == size_stack(stack2) ? ghc->j_index = 0 : ++ghc->j_index;
    (ghc->i_index__ + 1) == 255 ? ghc->i_index__ = 0 : ++ghc->i_index__;
}

void hash_key(Stack* stack, GHC* ghc, size_t index)
{
    //#if defined(_cr)    
    uint8_t smb = Tau[get_stack(stack, index).string ^ CUI32[index]];
    set_stack(stack, index, string(smb));
    /*#elif defined(_encr)
            uint8_t smb = get_stack(stack, index).string;
            for (size_t j = 0; j < 256; ++j)
            {
                if (smb == Tau[j])
                {
                    set_stack(stack, index, string((uint8_t)j ^ CUI32[index]));
                    break;
                }
            }
    #endif*/
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

