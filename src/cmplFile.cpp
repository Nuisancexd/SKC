#include "readFile.h"
#include "encrypt.h"

static void proc_bin_representation(int buffer_size, uint8_t* buffer, char* &dc)
{

	uint32_t** buff = new uint32_t*[buffer_size / 8];
	for (int i = 0; i < (buffer_size + 1) / 8; ++i)
	{
		buff[i] = new uint32_t[8];
	}

	int it = 0;
	for (int i = 0; i < (buffer_size + 1) / 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			buff[i][j] = buffer[it] - '0';
			it++;
		}
	}

	int sum = 0;
	it = 0;
	for (int i = 0; i < (buffer_size + 1) / 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			sum += buff[i][j] == 1 ? 1 << j : 0;
		}
		sum = gray_dencode(sum);
		dc[it] = sum;
		it++;
		sum = 0;		
	}
}

void read_dencrypt_file(const char* in, const char* out, const char* key)
{
	FILE* ptr;
	FILE* ptr2;
	errno_t err = fopen_s(&ptr, in, "r");
	errno_t err2 = fopen_s(&ptr2, out, "w");

	if (ptr == NULL || ptr2 == NULL)
	{
		std::cout << "Cant open file" << std::endl;
		return;
	}

	
	uint8_t* buffer = new uint8_t[1025];
	while(fgets((char*)buffer, 1025, ptr))
	{
		char* smbls = new char[(strlen((char*)buffer)) / 8];
		
		proc_bin_representation(strlen((char*)buffer), buffer, smbls);

		Stack* stack = new_stack(strlen((char*)buffer), STRING_TYPE);		

		for (size_t i = 0; i < strlen((char*)buffer) / 8; ++i)
		{
			push_stack(stack, string(smbls[i]));
		}
		delete[] smbls;
		std::fill(&buffer[0], &buffer[1025], 0);

		Stack* stack2 = new_stack(strlen(key), STRING_TYPE);

		for (int i = 0; i < strlen(key); ++i)
		{
			push_stack(stack2, string(key[i]));
		}

		
		hash_key(stack2);
		Hash_xor_key(stack2);
		merge_state_key(stack, stack2);
		dehash_state(stack);


		fwrite(get_arr(stack), size_stack(stack), 1, ptr2);

		free_stack(stack);
		free_stack(stack2);

	}


	fclose(ptr);
	fclose(ptr2);

	std::cout << "Completly encrypted.";
}

void read_encrypt_file(const char* in, const char* out, const char* key)
{	
	FILE* ptr1;
	FILE* ptr2;
	errno_t err1 = fopen_s(&ptr1, in, "r");
	errno_t err2 = fopen_s(&ptr2, out, "w");

	if (ptr1 == NULL || ptr2 == NULL)
	{
		std::cout << "Cant open file" << std::endl;
		return;
	}

	
	uint8_t* buffer = new uint8_t[1025];
	while (fgets((char*)buffer, 1025, ptr1))	
	{

		Stack* stack = new_stack(strlen((char*)buffer), STRING_TYPE);

		for (size_t i = 0; i < strlen((char*)buffer); ++i)
		{
			push_stack(stack, string(buffer[i]));
		}
		std::fill(&buffer[0], &buffer[1025], 0);
	
		Stack* stack2 = new_stack(strlen(key), STRING_TYPE);

		for (int i = 0; i < strlen(key); ++i)
		{
			push_stack(stack2, string(key[i]));
		}


		hash_state(stack);
		hash_key(stack2);
		Hash_xor_key(stack2);
		merge_state_key(stack, stack2);

		for (size_t i = 0; i < size_stack(stack); ++i)
		{
			Stack* stack_ = new_stack(8, INTEGER_TYPE);

			uint8_t smb = get_stack(stack, i).string;
			dec_to_bin(stack_, smb);	

			for (size_t i = 0; i < 8; ++i)
			{
				fprintf(ptr2, "%i", get_stack(stack_, i).integer);
			}
			free_stack(stack_);
		}
		free_stack(stack);
		free_stack(stack2);

	}


	fclose(ptr1);
	fclose(ptr2);

	std::cout << "Completly dencrypted.";
}


static void dec_to_bin(Stack* stack, int32_t val)
{
	val = gray_encode(val);
	size_t i;
	for (i = 0; val > 0; ++i)
	{
		push_stack(stack, integer(val % 2));
		val = val / 2;
	}
	if (i < 8)
	{
		for (; i < 8; ++i)
		{
			push_stack(stack, integer(0));
		}
	}
}


void save_link(const char* str)
{
	FILE* ptr;
	FILE* ptr_link;
	errno_t err = fopen_s(&ptr, "C:/links/linksClown.txt", "a+");	
	errno_t err_ = fopen_s(&ptr_link, str, "r");	

	if (ptr_link == NULL)
	{
		std::cout << "\nFile does not exist: " << str << std::endl;
		return;
	}

	if (ptr == NULL)
	{
		std::cout << "\nCreate folder:'links' in C:" << std::endl;		
		return;
	}	

	char r[] = { '\n' };

	fwrite(str, strlen(str), 1, ptr);
	fwrite(r, 1, 1, ptr);

	fclose(ptr);
	fclose(ptr_link);
}

void use_save_file(const char* key)
{
	FILE* ptr;
	errno_t err = fopen_s(&ptr, "C:/links/linksClown.txt", "r");

	if (ptr == NULL)
	{
		std::cout << "error_file: save the file" << std::endl;
		return;
	}

	char* buffer_in = new char[100];			
	fgets(buffer_in, 100, ptr);
	std::cout << "File input: " << buffer_in << std::endl;

	char* buffer_out = new char[100];
	fseek(ptr, strlen(buffer_in) + 1, SEEK_SET);
	fgets(buffer_out, 100, ptr);
	std::cout << "\t\t\t\t\t\tFile output: " << buffer_out << std::endl;
	fclose(ptr);

	buffer_in[strlen(buffer_in) - 1] = 0;
	buffer_out[strlen(buffer_out) - 1] = 0;

	bool what_ = false;
	char* buff_check = new char[3];
	FILE* ptr_check;
	errno_t err_ = fopen_s(&ptr_check, buffer_in, "r");
	fgets(buff_check, 3, ptr_check);
	fclose(ptr_check);

	if ((buff_check[0] == 48 && buff_check[1] == 48) || (buff_check[0] == 49 && buff_check[1] == 49)
		|| (buff_check[0] == 49 && buff_check[1] == 48) || (buff_check[0] == 48 && buff_check[1] == 49))
	{
		what_ = true;
	}
	delete[] buff_check;


	if (what_ == true)
	{
		read_dencrypt_file(buffer_in, buffer_out, key);
	}
	else
	{
		read_encrypt_file(buffer_in, buffer_out, key);
	}

	std::cout << "Success" << std::endl;
	fclose(ptr);
}
