#include <iostream>
#include <catch2/catch.hpp>
#include <sstream>
#include "[Task4] Crypt/CryptStream.h"

bool AreEqualString(std::string s1, std::string s2)
{
	return !s1.compare(s2);
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

TEST_CASE("CryptStream: One line string in input with only letters")
{
	std::string srcMessage = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\n";
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

TEST_CASE("CryptStream: One line string in input with only digits")
{
	std::string srcMessage = "123454321\n";
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

TEST_CASE("CryptStream: One line string in input with letters and digits")
{
	std::string srcMessage = "1 2 3 4 5 Coffee is going to hike for Cake\n";
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