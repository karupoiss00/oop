#pragma once
#include <map>
#include <array>
#include <optional>
#include <istream>

using CryptingKey = unsigned char;


enum class Operations
{
	Crypt,
	Decrypt
};

const std::string_view CRYPT_OPERATION_NAME = "crypt";
const std::string_view DECRYPT_OPERATION_NAME = "decrypt";
constexpr size_t BYTE_SIZE = 8;
const std::array<std::pair<unsigned, unsigned>, 8> cryptingMap = {
	std::pair(0, 2),
	std::pair(1, 3),
	std::pair(2, 4),
	std::pair(3, 6),
	std::pair(4, 7),
	std::pair(5, 0),
	std::pair(6, 1),
	std::pair(7, 5),
};

void CryptStream(std::istream& input, std::ostream& output, CryptingKey key);
void DecryptStream(std::istream& input, std::ostream& output, CryptingKey key);
std::optional<Operations> MapStringToOperation(const std::string operationName);