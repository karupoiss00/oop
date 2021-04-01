#include "DialogConsts.h"
#include "Dictionary.h"

using namespace std;
using namespace boost;

bool LoadDictionary(const string& fileName, Dictionary& dct)
{
	string lexeme, translation;
	ifstream input(fileName);

	if (!input.is_open())
	{
		return false;
	}

	while (getline(input, lexeme) && getline(input, translation))
	{
		dct.insert(make_pair(lexeme, translation));
	}

	return true;
}

bool NeedDictionarySaving(pInputFn inp, pOutputFn out)
{
	string confirm;

	out(MSG_CONFIRM_SAVE_CHANGES + "\n");
	inp(confirm);

	return (confirm == "Y" || confirm == "y");
}

bool SaveDictionary(const string& fileName, Dictionary& dct)
{
	ofstream output(fileName);

	if (!output.is_open())
	{
		return false;
	}

	for (Dictionary::iterator it = dct.begin(); it != dct.end(); ++it)
	{
		output << (*it).first << endl;
		output << (*it).second << endl;
	}

	return true;
}

void StartSessionWithUser(Dictionary& dct, pInputFn read, pOutputFn print)
{
	string lexeme;

	print("\n>");

	while (getline(cin, lexeme))
	{
		if (lexeme == "...")
		{
			break;
		}

		Translate(lexeme, dct, read, print);
		print("\n>");
	}
}

void Translate(string& lexeme, Dictionary& dct, pInputFn read, pOutputFn print)
{
	string lowerCaseLexeme = lexeme;
	transform(lowerCaseLexeme.begin(), lowerCaseLexeme.end(), lowerCaseLexeme.begin(), ::tolower);

	if (!IsLexemeRussian(lowerCaseLexeme))
	{
		if (!TranslateLexeme(lowerCaseLexeme, dct, print))
		{
			InputTranslation(lowerCaseLexeme, dct, ENGLISH, read, print);
		}
	}
	else
	{
		if (!TranslateLexemeReverse(lexeme, dct, print))
		{
			InputTranslation(lexeme, dct, RUSSIAN, read, print);
		}
	}
}

unsigned TranslateLexeme(const string& lexeme, Dictionary& dct, pOutputFn print)
{
	if (!dct.count(lexeme))
	{
		return 0;
	}

	pair<Dictionary::iterator, Dictionary::iterator> entrys;
	entrys = dct.equal_range(lexeme);
	unsigned entrysCount = 0;

	for (Dictionary::iterator it = entrys.first; it != entrys.second; ++it)
	{
		if (it != entrys.first)
		{
			print(", ");
		}
		print(it->second);
		++entrysCount;
	}

	return entrysCount;
}

unsigned TranslateLexemeReverse(const string& lexeme, Dictionary& dct, pOutputFn out)
{
	unsigned entrysCount = 0;

	for (Dictionary::iterator it = dct.begin(); it != dct.end(); ++it)
	{
		if (it->second == lexeme)
		{
			if (entrysCount)
			{
				out(", ");
			}
			out((*it).first);
			++entrysCount;
		}
	}

	return entrysCount;
}

void InputTranslation(string& lexeme, Dictionary& dct, bool isEnglish, pInputFn read, pOutputFn print)
{
	string translation;

	print((format(MSG_UNKNOWN_WORD) % lexeme).str() + "\n>");
	read(translation);

	if (!translation.length())
	{
		print((format(MSG_IGNORED_WORD) % lexeme).str());
		return;
	}

	if (!isEnglish)
	{
		swap(lexeme, translation);
	}

	dct.insert(make_pair(lexeme, translation));
	print((format(MSG_TRANSLATE_WORD) % lexeme % translation).str());
}

bool IsLexemeRussian(const string& lexeme)
{
	auto IsRussianChar = [](char ch) { return ((ch >= 'а') && (ch <= 'я') || (ch == 'ё')); };
	return any_of(lexeme.begin(), lexeme.end(), IsRussianChar);
}

void Input(string& str)
{
	getline(cin, str);
}

void Output(const string& str)
{
	cout << str;
}