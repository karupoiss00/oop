#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <string>
#include <boost/format.hpp>

using Dictionary = std::multimap<std::string, std::string>;
using pInputStream = void(*)(std::string&);
using pOutputStream = void(*)(const std::string&);

enum Languages
{
	RUSSIAN = 0,
	ENGLISH
};

void Input(std::string& str);
void Output(const std::string& str);

bool LoadDictionary(const std::string& fileName, Dictionary& dct);
bool SaveDictionary(const std::string& fileName, Dictionary& dct);

void StartSessionWithUser(Dictionary& dct, pInputStream read, pOutputStream print);
void Translate(std::string& lexeme, Dictionary& dct, pInputStream read, pOutputStream print);

unsigned TranslateLexeme(const std::string& lexeme, Dictionary& dct, pOutputStream print);
unsigned TranslateLexemeReverse(const std::string& lexeme, Dictionary& dct, pOutputStream print);

void InputTranslation(std::string& lexeme, Dictionary& dct, bool isEnglish, pInputStream read, pOutputStream print);
bool IsLexemeRussian(const std::string& lexeme);

bool NeedDictionarySaving(pInputStream inp, pOutputStream out);