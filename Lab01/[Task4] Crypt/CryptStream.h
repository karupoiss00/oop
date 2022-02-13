#pragma once
#include <map>
#include <fstream>

using CryptingKey = unsigned char;

const size_t BYTE_SIZE = 8;
const std::string_view CRYPT_OPERATION = "crypt";
const std::string_view DECRYPT_OPERATION = "decrypt";
const std::map<size_t, size_t> cryptingMap = {
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