#include "Compiler.h"

Compiler::Compiler(std::string path) : file(path) {}

std::string Compiler::work_brackets(std::string key, std::string line)
{
	std::string returner = key + " "; std::string boolean, in, options; int counter = 0;
	for (int i = key.size(); i < line.size(); i++)
	{
		if (counter == 0)
		{
			if (line[i] == '(') counter++;
			else options += line[i];
		}
		else if (counter == 1)
		{
			if (line[i] == ')') counter++;
			else boolean += line[i];
		}
		else if (counter == 2)
		{
			in += line[i];
		}
	}
	returner += "(" + boolean + ")" + "{" + compile_line(in) + "}";
	return returner;
}

std::string Compiler::compile_function_define(std::string segment)
{
	std::string name, parameters, options, in; int counter = 0;
	for (int i = 0; i < segment.size(); i++)
	{
		if (counter == 0)
		{
			if (segment[i] == '(') counter++;
			else name += segment[i];
		}
		else if (counter == 1)
		{
			if (segment[i] == ')') counter++;
			else parameters += segment[i];
		}
		else if (counter == 2)
		{
			if (segment[i] == ':') { counter++; i++; }
			else options += segment[i];
		}
		else if (counter == 3)
		{
			in += segment[i];
		}
	}

	std::string returner;
	returner = "void " + name + "(" + parameters + "){" + compile_line(in) + "}";
	return returner;
}

std::string Compiler::compile_func(std::string line)
{
	std::string name, parameter; int counter = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (counter == 0)
		{
			if (line[i] == '(') counter++;
			else name += line[i];
		}
		else if (counter == 1)
		{
			if (line[i] == ')') break;
			else parameter += line[i];
		}
	}
	return name + "(" + parameter + ");";
}

std::string Compiler::compile_extern(std::string line)
{
	std::string returner;
	std::vector<std::string> cutted = cut(line, " ");
	if (cutted[1] == "C++")
	{
		for (int i = 2; i < cutted.size(); i++) returner += cutted[i] + " ";
	}
	return returner;
}

std::string Compiler::compile_var_define(std::string line)
{
	std::string later;
	if (keyCodeC(line, "int"))
	{
		for (int i = 4; i < line.size(); i++) later += line[i];
		return "int " + later + ";";
	}
	else if (keyCodeC(line, "string"))
	{
		for (int i = 7; i < line.size(); i++) later += line[i];
		return "std::string " + later + ";";
	}
	else if (keyCodeC(line, "float"))
	{
		for (int i = 6; i < line.size(); i++) later += line[i];
		return "float " + later + ";";
	}
	else return "";
}

std::string Compiler::compile_line(std::string line)
{
	std::string returner;
	if (hmint(line, "extern") == 0 && hmint(line, ";") > 0) for (std::string cutted : cut(line, ";")) returner += compile_line(cutted);
	else if (keyCodeC(line, "if")) returner = work_brackets("if", line);
	else if (keyCodeC(line, "while")) returner = work_brackets("while", line);
	else if (keyCodeC(line, "extern")) returner = compile_extern(line);
	else if (Lexer::isThat_func_definition(line)) returner = compile_function_define(line);
	else if (Lexer::isThat_func(line)) returner = compile_func(line);
	else if (Lexer::isThat_var_definition(line)) returner = compile_var_define(line);
	return returner;
}

void Compiler::compile(std::string ct)
{
	std::fstream compiled_file(ct); std::string line;
	while (std::getline(file, line)) compiled_file << compile_line(line);
	std::cout << "Compile ended. Converted to cpp at " << ct << std::endl;
}