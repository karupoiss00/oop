#pragma once
#include <string>
#include <algorithm>
#include "Translations.h"
#include "Errors.h"

unsigned PreporationToConverting(std::string& str, unsigned radix, unsigned& power, bool& isNegative);
unsigned CharToInt(char ch, bool& wasError);
int StringToInt(std::string str, unsigned radix, bool& wasError);
char IntToChar(int number);
std::string IntToString(int number, unsigned radix, std::string& errorMsg);