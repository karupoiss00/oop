#pragma once
#include <iostream>
#include "StringIntCasts.h"
#include "Errors.h"

std::string ConvertNumber(const std::string& numberStr, unsigned fromRadix, unsigned toRadix);
int RadixInMaxPower(unsigned radix, unsigned maxExponent, bool isNegative, bool& wasError);
bool CanAccumulate(unsigned& result, unsigned digit, unsigned radixInMaxPow, bool isNegative);