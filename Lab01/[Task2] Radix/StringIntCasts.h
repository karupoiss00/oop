#pragma once
#include <string>
#include <algorithm>
#include "Translations.h"
#include "Errors.h"

unsigned PreparationToConverting(std::string& str, unsigned radix, unsigned& radixInMaxPow, bool& isNegative);
unsigned CharToInt(char ch, bool& wasError);
int StringToInt(std::string str, unsigned radix, bool& wasError);
char IntToChar(int number);
std::string IntToString(int number, unsigned radix, std::string& errorMsg);