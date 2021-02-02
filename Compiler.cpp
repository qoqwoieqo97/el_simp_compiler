#include "Compiler.h"

Compiler::Compiler(std::string path)
{
	to_compile.open(path,std::ios::app);
}

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
			else if (segment[i] == ' ');
			else options += segment[i];
		}
		else if (counter == 3)
		{
			in += segment[i];
		}
	}
	std::string return_type = options == "string" ? "std::string" : options;

	return return_type + " " + name + "(" + parameters + "){" + compile_line(in) + "}";
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
	/*std::string resultPar;
	for (int i = 0; i < parameter.size(); i++)
	{
		if (stringController(parameter, "string", i)) resultPar += "std::string";
		else resultPar += parameter;
	}*/
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
	else if (keyCodeC(line, "drawning"))
	{
		for (int i = 8; i < line.size(); i++) later += line[i];
		return "sf::Sprite " + later + ";";
	}
	else if (keyCodeC(line, "float"))
	{
		for (int i = 6; i < line.size(); i++) later += line[i];
		return "float " + later + ";";
	}
	else return "";
}

std::string Compiler::compile_libpp(std::string libpp_segment)
{
	bool inParam = false; std::string param;
	for (char c : libpp_segment)
	{
		if (c == '(') inParam = true;
		else if (c == ')') break;
		else if (inParam) param += c;
	}
	return "#include \"" + Lexer::getValue(param, Types::STRING) + "\"\n";
}

std::string Compiler::compile_return(std::string return_segment)
{
	return return_segment+';';
}
std::string Compiler::compile_command(std::string compiler_segment)
{
	std::string command;
	for (int i = 10; i < compiler_segment.size(); i++)
	{
		command += compiler_segment[i];
	}
	if (command == "main")
	{
		isItIn = true;
		return "int main(){";
	}
	return "";
}

std::string Compiler::compile_load(std::string cs)
{
	std::string path = "";
	for (int i = 5; i < cs.size(); i++)
	{
		path += cs[i];
	}


	compiler_while(path);
	return "/* loaded " + path + " here */";
}

std::string Compiler::compile_line(std::string line)
{
	std::string returner;
	if (keyCodeC(line, "//") || line == "");
	else if (hmint(line, "extern") == 0 && keyCodeC(line,"while") == false && hmint(line, ";") > 0 && !Lexer::isThat_func_definition(line)) for (std::string cutted : cut(line, ";")) returner += compile_line(cutted);
	else if (keyCodeC(line, "if")) returner = work_brackets("if", line);
	else if (keyCodeC(line, "while")) returner = work_brackets("while", line);
	else if (keyCodeC(line, "extern")) returner = compile_extern(line);
	else if (keyCodeC(line, "lib++")) returner = compile_libpp(line);
	else if (keyCodeC(line, "return")) returner = compile_return(line);
	else if (keyCodeC(line, "load")) returner = compile_load(line);
	else if (keyCodeC(line, "#compiler")) returner = compile_command(line);
	else if (Lexer::isThat_func_definition(line)) returner = compile_function_define(line);
	else if (Lexer::isThat_func(line)) returner = compile_func(line);
	else if (Lexer::isThat_var_definition(line)) returner = compile_var_define(line);
	return returner;
}

void Compiler::compiler_while(std::string rp)
{
	std::string line;
	std::fstream read_file(rp);
	while (std::getline(read_file, line)) to_compile << compile_line(line);
	if (isItIn)to_compile << '}';
}

void Compiler::main_compile(std::string rp)
{
	compiler_while(rp);
	std::cout << "Compile end" << std::endl;
}