#pragma once
#include <fstream>

using CryptingKey = unsigned char;

void CryptStream(std::istream& input, std::ostream& output, CryptingKey key);
void DecryptStream(std::istream& input, std::ostream& output, CryptingKey key);