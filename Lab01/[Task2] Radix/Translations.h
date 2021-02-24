#pragma once
#include <iostream>
#include "StringIntCasts.h"
#include "Errors.h"

std::string ConvertNumber(const std::string& numberStr, unsigned fromRadix, unsigned toRadix);
int RadixInMaxPower(unsigned radix, int maxExponent, bool isNegative, bool& wasError);
bool CanAccumulate(unsigned& result, unsigned digit, unsigned power, bool isNegative);