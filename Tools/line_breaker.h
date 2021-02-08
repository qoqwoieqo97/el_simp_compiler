#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../emils_lib-main/emils_lib.h"


namespace LB
{
	bool isEmpty(std::string s)
	{
		int counter = 0;
		for (char c : s) if (c != ' ') counter++;
		return counter == 0;
	}

	int get_textStarting(std::string string,int starting_pos = 0)
	{
		for (int i = starting_pos; i < string.size(); i++)
		{
			if (string[i] != ' ') return i;
		}
		return -1;
	}

	std::string get_all(std::fstream &file)
	{
		std::string result = "",line = "";
		while (getline(file, line))
		{
			result = el::StrCalc::add(result, line, result.size());
		}
		return result;
	}

	std::vector<std::string> line_breaker(std::string string)
	{
		std::vector<std::string> result;
		std::string wll_add; int infunc = 0; bool in_text = false;
		for (char c : string)
		{
			if (infunc == 0 && !in_text)
			{
				if (c == '{') infunc++;
				else if (c == '"') in_text = true;
				else if (c == ';') { result.push_back(wll_add); wll_add = ""; continue; }
			}
			else
			{
				if (c == '{') infunc++;
				else if (c == '}') infunc--;
				else if (c == '"') in_text = false;
			}

			wll_add += c;
		}
		result.push_back(wll_add);
		return result;
	}
}