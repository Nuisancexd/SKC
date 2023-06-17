#pragma once

#include "stack.h"


extern void read_dencrypt_file(const char* in, const char* out, const char* key);

extern void read_encrypt_file(const char* in, const char* out, const char* key);

static void proc_bin_representation(int buffer_size, uint8_t* buffer, char*& dc);

static void dec_to_bin(Stack* stack, int32_t val);

extern void save_link(const char* str);

extern void use_save_file(const char* key);
