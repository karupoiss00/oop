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

typedef std::multimap<std::string, std::string> Dictionary;
typedef void (*pInput)(std::string&);
typedef void (*pOutput)(const std::string&);

enum Languages
{
	RUSSIAN = 0,
	ENGLISH
};

void Input(std::string& str);
void Output(const std::string& str);

bool LoadDictionary(const std::string& fileName, Dictionary& dct);
bool SaveDictionary(const std::string& fileName, Dictionary& dct);

void StartSessionWithUser(Dictionary& dct, pInput read, pOutput print);
void Translate(std::string& lexeme, Dictionary& dct, pInput read, pOutput print);

unsigned TranslateLexeme(const std::string& lexeme, Dictionary& dct, pOutput print);
unsigned TranslateLexemeReverse(const std::string& lexeme, Dictionary& dct, pOutput print);

void InputTranslation(std::string& lexeme, Dictionary& dct, bool isEnglish, pInput read, pOutput print);
bool IsLexemeRussian(const std::string& lexeme);

bool NeedDictionarySaving(pInput inp, pOutput out);