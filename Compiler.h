#pragma once
#include <iostream>
#include <fstream>
#include "Lexer.h"

class Compiler
{
private:
	std::fstream file; bool isItIn = false;
public:
	Compiler(std::string filePath);

	std::string work_brackets(std::string key, std::string line);
	std::string compile_func(std::string func_segment);
	std::string compile_function_define(std::string func_segment);
	std::string compile_extern(std::string extern_segment);
	std::string compile_var_define(std::string var_segment);
	std::string compile_libpp(std::string libpp_segment);
	std::string compile_return(std::string return_segment);
	std::string compile_command(std::string compiler_segment);

	std::string compile_line(std::string line);
	void compile(std::string compile_to);
};