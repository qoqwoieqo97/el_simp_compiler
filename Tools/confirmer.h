#pragma once
#include <string>
#include <iostream>


namespace CON
{
	bool is_int(char c)
	{
		return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
	}
	bool is_int(std::string s)
	{
		for (char c : s) if (!is_int(c)) return false;
		return true;
	}
	bool is_empty(std::string s)
	{
		for (char c : s) if (c != ' ') return false;
		return true;
	}
}