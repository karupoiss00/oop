#include <iostream>
#include <catch2/catch.hpp>
#include <cmath>
#include <chrono>
#include "..\set_of_primes\PrimesGenerator.h"

using namespace std;

#ifdef NDEBUG
TEST_CASE("GeneratePrimeNumbersSet: check timings and count of primes")
{
    auto t1 = std::chrono::high_resolution_clock::now();
    set<size_t> primes = GeneratePrimeNumbersSet(100000000);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    REQUIRE(duration < 12);
    REQUIRE(primes.size() == 5761455);
}
#endif

TEST_CASE("GeneratePrimeNumbersSet: check 0 value")
{
    set<size_t> primes = GeneratePrimeNumbersSet(0);
    REQUIRE(primes.size() == 0);
}

TEST_CASE("GeneratePrimeNumbersSet: check 2 value (bound)")
{
    set<size_t> primes = GeneratePrimeNumbersSet(2);
    set<size_t> expectedPrimes{ 2 };
    REQUIRE(primes == expectedPrimes);
}

TEST_CASE("GeneratePrimeNumbersSet: check 7 value (prime number bound)")
{
    set<size_t> primes = GeneratePrimeNumbersSet(7);
    set<size_t> expectedPrimes{ 2, 3, 5, 7 };
    REQUIRE(primes == expectedPrimes);
}