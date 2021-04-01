#include <iostream>
#include <catch2/catch.hpp>
#include <cmath>
#include <chrono>
#include "..\set_of_primes\PrimesGenerator.h"

using namespace std;

TEST_CASE("GeneratePrimeNumbersSet: check timings and count of primes")
{
    auto t1 = std::chrono::high_resolution_clock::now();
    set<size_t>&& primes = GeneratePrimeNumbersSet(100000000);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    REQUIRE(duration < 12);
    REQUIRE(primes.size() == 5761455);
}