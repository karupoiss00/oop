#pragma once
#include <fstream>

void CryptStream(std::istream& input, std::ostream& output, int key);
void DecryptStream(std::istream& input, std::ostream& output, int key);