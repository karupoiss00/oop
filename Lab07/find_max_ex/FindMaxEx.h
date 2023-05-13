#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	size_t maxElementIndex = 0;

	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (less(arr[maxElementIndex], arr[i]))
		{
			maxElementIndex = i;
		}
	}

	maxValue = arr[maxElementIndex];

	return true;
}

template <typename T>
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	auto DefaultComparator = [](T const& lhs, T const& rhs)
	{
		return lhs < rhs;
	};

	return FindMax(arr, maxValue, DefaultComparator);
}