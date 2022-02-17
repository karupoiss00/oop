#pragma once
#include <map>
#include <istream>

using CryptingKey = unsigned char;

enum class Operations
{
	Crypt,
	Decrypt
};

constexpr size_t BYTE_SIZE = 8;
const std::string_view CRYPT_OPERATION_NAME = "crypt";
const std::string_view DECRYPT_OPERATION_NAME = "decrypt";
const std::map<unsigned, unsigned> cryptingMap = {
	{0, 2},
	{1, 3},
	{2, 4},
	{3, 6},
	{4, 7},
	{5, 0},
	{6, 1},
	{7, 5},
};

void CryptStream(std::istream& input, std::ostream& output, CryptingKey key);
void DecryptStream(std::istream& input, std::ostream& output, CryptingKey key);