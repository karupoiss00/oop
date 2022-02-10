#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "OperationNames.h"
#include "CryptingMap.h"
#include "CryptStream.h"

using namespace std;

char BitsetToChar(bitset<8>& bits)
{
	unsigned long i = bits.to_ulong();
	return static_cast<char>(i);
}

char CryptByte(char srcByte, int key)
{
	char xoredByte = srcByte ^ key;
	bitset<8> uncryptedBitmap(xoredByte);
	bitset<8> cryptedBitmap;

	for (const auto& [srcBitIndex, destBitIndex] : cryptingMap) {
		cryptedBitmap.set(destBitIndex, uncryptedBitmap[srcBitIndex]);
	}

	return BitsetToChar(cryptedBitmap);
}

char DecryptByte(char cryptedByte, int key)
{
	bitset<8> cryptedBitmap(cryptedByte);
	bitset<8> decryptedBitmap;

	for (const auto& [destBitIndex, srcBitIndex] : cryptingMap) {
		decryptedBitmap.set(destBitIndex, cryptedBitmap[srcBitIndex]);
	}

	char unxoredChar = BitsetToChar(decryptedBitmap);

	return unxoredChar ^ key;
}

string CryptString(const string& srcStr, int key)
{
	string cryptedString = "";
	for (const auto& symbol : srcStr) {
		char cryptedSymbol = CryptByte(symbol, key);
		cryptedString.push_back(cryptedSymbol);
	}
	return cryptedString;
}

string DecryptString(const string& cryptedStr, int key)
{
	string decryptedString = "";
	for (const auto& symbol : cryptedStr) {
		char decryptedSymbol = DecryptByte(symbol, key);
		decryptedString.push_back(decryptedSymbol);
	}
	return decryptedString;
}

void CryptStream(istream& input, ostream& output, int key)
{
	string line;
	while (getline(input, line))
	{
		output << CryptString(line, key);
		if (!output.eof())
		{
			cout << endl;
		}
	}
}

void DecryptStream(istream& input, ostream& output, int key)
{
	string line;
	while (getline(input, line))
	{
		output << DecryptString(line, key);
		if (!output.eof())
		{
			cout << endl;
		}
	}
}