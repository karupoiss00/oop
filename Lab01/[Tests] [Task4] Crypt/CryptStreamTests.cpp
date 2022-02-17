#include <iostream>
#include <catch2/catch.hpp>
#include <sstream>
#include "[Task4] Crypt/CryptStream.h"

bool AreEqualString(std::string s1, std::string s2)
{
	return !s1.compare(s2);
}

bool IsAllCharsUnique(std::string str)
{
	sort(str.begin(), str.end());

	for (unsigned i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == str[i + 1])
		{
			return false;
		}
	}

	return true;
}

TEST_CASE("CryptStream: Empty string in input")
{
	CryptingKey key = 1;
	std::istringstream inputNotCrypted("");
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);


	std::istringstream inputCrypted(outputCrypted.str());
	std::ostringstream outputDecrypted;
	DecryptStream(inputCrypted, outputDecrypted, key);

	const std::string decryptedMessage = outputDecrypted.str();
	REQUIRE(AreEqualString(decryptedMessage, ""));
}

TEST_CASE("CryptStream: All bytes unique after decrypting")
{
	CryptingKey key = 1;
	std::string allBytesChars = "";
	for (unsigned i = 0; i < 0b11111111; i++) 
	{
		allBytesChars += static_cast<char>(i);
	}

	std::istringstream inputNotCrypted(allBytesChars);
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);

	REQUIRE(IsAllCharsUnique(outputCrypted.str()));

	std::istringstream inputCrypted(outputCrypted.str());
	std::ostringstream outputDecrypted;
	DecryptStream(inputCrypted, outputDecrypted, key);

	const std::string decryptedMessage = outputDecrypted.str();
	REQUIRE(AreEqualString(decryptedMessage, allBytesChars));
}

TEST_CASE("CryptStream: Only spaces multi line string")
{
	std::string srcMessage = "     \n     \n     \n";
	CryptingKey key = 1;
	std::istringstream inputNotCrypted(srcMessage);
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);


	std::istringstream inputCrypted(outputCrypted.str());
	std::ostringstream outputDecrypted;
	DecryptStream(inputCrypted, outputDecrypted, key);

	const std::string decryptedMessage = outputDecrypted.str();
	REQUIRE(AreEqualString(decryptedMessage, srcMessage));
}

TEST_CASE("CryptStream: Only line breaks string")
{
	std::string srcMessage = "\n\n\n\n\n\n\n\n";
	CryptingKey key = 1;
	std::istringstream inputNotCrypted(srcMessage);
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);


	std::istringstream inputCrypted(outputCrypted.str());
	std::ostringstream outputDecrypted;
	DecryptStream(inputCrypted, outputDecrypted, key);

	const std::string decryptedMessage = outputDecrypted.str();
	REQUIRE(AreEqualString(decryptedMessage, srcMessage));
}

TEST_CASE("CryptStream: \'C\' chars converting to \n")
{
	std::string srcMessage = "CCCCCC\n";
	CryptingKey key = 1;
	std::istringstream inputNotCrypted(srcMessage);
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);


	std::istringstream inputCrypted(outputCrypted.str());
	std::ostringstream outputDecrypted;
	DecryptStream(inputCrypted, outputDecrypted, key);

	const std::string decryptedMessage = outputDecrypted.str();
	REQUIRE(AreEqualString(decryptedMessage, srcMessage));
}