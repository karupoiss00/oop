#include <iostream>
#include <catch2/catch.hpp>
#include <sstream>
#include "[Task4] Crypt/CryptStream.h"

bool AreEqualString(std::string s1, std::string s2)
{
	return !s1.compare(s2);
}

TEST_CASE("CryptStream: Check is crypted string differ from original string")
{
	CryptingKey key = 1;
	std::string srcMessage = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\n";
	std::istringstream inputNotCrypted(srcMessage);
	std::ostringstream outputCrypted;
	CryptStream(inputNotCrypted, outputCrypted, key);

	REQUIRE(!AreEqualString(srcMessage, outputCrypted.str()));
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
	std::string srcMessage = "123456789\n";
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
	std::string srcMessage = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz123456789\n";
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

TEST_CASE("CryptStream: Only spaces one line string")
{
	std::string srcMessage = "     \n";
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

TEST_CASE("CryptStream: Multi line string in input with only letters")
{
	std::string srcMessage = 
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\n"
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\n"
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\n";
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

TEST_CASE("CryptStream: Multi line string in input with only digits")
{
	std::string srcMessage = "123456789\n123456789\n123456789\n";
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

TEST_CASE("CryptStream: Multi line string in input with letters and digits")
{
	std::string srcMessage = 
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz123456789\n"
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz123456789\n"
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz123456789\n";
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