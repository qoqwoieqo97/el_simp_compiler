#include "Compiler.h"
#include "../Lexer/Lexer.h"

std::string get_all(std::fstream& file)
{
	std::string result = "", line = "";
	while (getline(file, line))
	{
		result += line;
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

bool itsw(std::string t, std::string wt)
{
	for (int i = 0; i < t.size() && i < wt.size(); i++) if (t[i] != wt[i]) return false; return true;
}



void Compiler::compile(std::string filePath)
{
	std::fstream file(filePath);
	std::string allof = get_all(file);

	for (std::string line : line_breaker(allof))
	{
		compile_line(line);
	}
}

void Compiler::compile_line(std::string line)
{
	if (Lexer::is_that_objectDefine(line)) compile_objectDefine(line);
	else if (isThat_privateFunction(line)) compile_privateFunction(line);
	else if (isThat_summonFunction(line)) compile_summonFunction(line);
	else if (itsw("var", line)) compile_varDefining(line);
}

bool Compiler::isThat_privateFunction(std::string line)
{
	bool req = false;
	for (LanObject ob : objects) if (itsw(line, ob.id)) req= true;
	if(!req) return false;
	return Lexer::control_lotOChars("()->{}",line);
}

bool Compiler::isThat_summonFunction(std::string line)
{
	bool req = false;
	for (func ob : funcs) if (itsw(line, ob.name)) req = true;
	if (!req) return false;
	return Lexer::control_lotOChars("()", line);
}

void Compiler::compile_privateFunction(std::string line)
{
	std::string object_name, function_name, parameter, func_doing; int counter = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (counter == 0 && line[i] == '.')counter++;
		else if (counter == 0 && line[i] != ' ')object_name += line[i];

		else if (counter == 1 && line[i] == '(')counter++;
		else if (counter == 1 && line[i] != ' ')function_name += line[i];

		else if (counter == 2 && line[i] == ')')counter++;
		else if (counter == 2 && line[i] != ' ')parameter += line[i];

		else if (counter == 3 && line[i] == '{')counter++;

		else if (counter == 4 && line[i] == '}')counter++;
		else if (counter == 4 && line[i] != ' ')func_doing += line[i];
	}
	compile_function(object_name, function_name, func_doing);
}

void Compiler::compile_function(std::string on, std::string fn, std::string fd)
{
	if (fn == "onClick")
	{
		for (int i = 0; i < objects.size(); i++)
		{
			std::cout << "Testing:" << objects[i].id <<" " << on << std::endl;
			if (objects[i].id == on) objects[i].on_click = fd;
		}
	}
	else
	{
		general_script += "function " + on + "_" + fn + "(){" + fd + "} \n";
		funcs.push_back({ on + "." + fn });
	}
}

void Compiler::compile_objectDefine(std::string line)
{
	std::string name, text, css;
	int counter = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (counter == 0 && line[i] == '{') counter++;
		else if (counter == 0 && line[i] != ' ')name += line[i];

		else if (counter == 1 && line[i] == '}') counter++;
		else if (counter == 1 && line[i] != ' ') css += line[i];
	}

	LanObject obj; obj.type = HTML_Type::p; obj.id = name; obj.style = css;
	objects.push_back(obj);
}



void Compiler::compile_varDefining(std::string line)
{
	std::string var_name, start_value;
	int counter = 0;
	for (int i = 3; i < line.size(); i++)
	{
		if (counter == 0 && line[i] == '=') counter++;
		else if (counter == 0 && line[i] != ' ') var_name += line[i];
		else if (counter == 1)start_value += line[i];
	}
	/* Compiling Var */
	compile_var(var_name, start_value);
}

void Compiler::compile_summonFunction(std::string line)
{
	std::string result;
	for (char c : line)
	{
		result += c == '.' ? '_' : c;
	}
	general_script += result;
}

void Compiler::compile_var(std::string name, std::string value)
{
	if (name == "text")
	{
		title = value;
	}
	else
	{
		general_script += "var " + name + " " + value + ";";
	}
}

void Compiler::save_html(std::string p)
{
	std::fstream file(p);

	file << "<html>" << std::endl;
	file << "<head><title>" << title << "</title>" << std::endl;
	if(general_script!="") file << "<script>" << general_script << "</script>" << std::endl;
	file << "</head>"<<std::endl;
	file << "<body>" << std::endl;
	for (LanObject obj : objects)
	{
		file << obj.getHTML() << std::endl;
	}
	file << "</body></html>" << std::endl;
}