#include "PrimesGenerator.h"

using namespace std;

set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::set<size_t> primes;

	if (upperBound < 2)
	{
		return primes;
	}

	vector<bool> sieve;
	sieve.assign(upperBound + 1, true);


	size_t sieveSize = sieve.size();

	for (size_t i = 4; i < sieveSize; i += 2)
	{
		sieve[i] = false;
	}

	primes.insert(2);

	for (size_t i = 3; i < sieveSize; i += 2)
	{
		if (!sieve[i])
		{
			continue;
		}

		primes.insert(primes.end(), i);

		for (size_t j = i + i * 2; j < sieveSize; j += i * 2)
		{
			sieve[j] = false;
		}
	}

	return primes;
}