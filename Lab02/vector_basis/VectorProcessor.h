#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool ParseFloatsToVector(std::istream& input, std::vector<float>& v);
bool AddThreeMinElements(std::vector<float>& v);
void PrintVectorOfFloats(const std::vector<float>& v);