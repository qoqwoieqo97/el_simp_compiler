#pragma once
#include "../Lexer/Lexer.h"
class Compiler
{
private:
	std::fstream html_compile;
public:
	Compiler(std::string html_path);
};