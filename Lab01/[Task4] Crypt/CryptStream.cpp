#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "OperationNames.h"
#include "CryptingMap.h"
#include "CryptStream.h"

using namespace std;

const size_t BYTE_SIZE = 8;

char mapBitsInByte(char byteToMapping, char& byteFromMapping, size_t& mask, int& shift)
{
	if (shift > 0)
	{
		byteToMapping |= (byteFromMapping & mask) << shift;
	}
	else
	{
		byteToMapping |= (byteFromMapping & mask) >> -shift;
	}

	return byteToMapping;
}

char CryptByte(char srcByte, CryptingKey key)
{
	char xoredSrcByte = srcByte ^ key;
	char cryptedByte = static_cast<char>(0);

	for (const auto& [srcBitIndex, destBitIndex] : cryptingMap)
	{
		size_t mask = static_cast<size_t>(pow(2, srcBitIndex));
		int shift = destBitIndex - srcBitIndex;
		cryptedByte = mapBitsInByte(cryptedByte, xoredSrcByte, mask, shift);
	}

	return cryptedByte;
}

char DecryptByte(char cryptedByte, CryptingKey key)
{
	char decryptedByte = static_cast<char>(0);

	for (const auto& [destBitIndex, srcBitIndex] : cryptingMap)
	{
		size_t mask = static_cast<size_t>(pow(2, srcBitIndex));
		int shift = destBitIndex - srcBitIndex;
		decryptedByte = mapBitsInByte(decryptedByte, cryptedByte, mask, shift);
	}
	return decryptedByte ^ key;
}

string CryptString(const string& srcStr, CryptingKey key)
{
	string cryptedString = "";
	for (const auto& symbol : srcStr)
	{
		char cryptedSymbol = CryptByte(symbol, key);
		cryptedString.push_back(cryptedSymbol);
	}
	return cryptedString;
}

string DecryptString(const string& cryptedStr, CryptingKey key)
{
	string decryptedString = "";
	for (const auto& symbol : cryptedStr)
	{
		char decryptedSymbol = DecryptByte(symbol, key);
		decryptedString.push_back(decryptedSymbol);
	}
	return decryptedString;
}

void CryptStream(istream& input, ostream& output, CryptingKey key)
{
	string line;
	while (getline(input, line))
	{
		output << CryptString(line, key);
		if (!output.eof())
		{
			output << endl;
		}
	}
}

void DecryptStream(istream& input, ostream& output, CryptingKey key)
{
	string line;
	while (getline(input, line))
	{
		output << DecryptString(line, key);
		if (!output.eof())
		{
			output << endl;
		}
	}
}