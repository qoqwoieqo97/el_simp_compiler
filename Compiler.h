#pragma once
#include <iostream>
#include <fstream>
#include "Lexer.h"

class Compiler
{
private:
	std::fstream to_compile; bool isItIn = false;
public:
	Compiler(std::string to_compile_path);

	std::string work_brackets(std::string key, std::string line);
	std::string compile_func(std::string func_segment);
	std::string compile_function_define(std::string func_segment);
	std::string compile_extern(std::string extern_segment);
	std::string compile_var_define(std::string var_segment);
	std::string compile_libpp(std::string libpp_segment);
	std::string compile_return(std::string return_segment);
	std::string compile_command(std::string compiler_segment);
	std::string compile_load(std::string compiler_segment);

	void compiler_while(std::string reading_path);
	std::string compile_line(std::string line);
	void main_compile(std::string reading_path);
};