#pragma once
#include <vector>
namespace US
{
	template<typename T>
	std::vector<T> get_vector(T first_var)
	{
		std::vector<T> result;
		result.push_back(first_var);
		return result;
	}

	template<typename T>
	std::vector<T> get_vector()
	{
		std::vector<T> result;
		return result;
	}
}