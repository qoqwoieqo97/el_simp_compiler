#pragma once
#include <iostream>
#include <fstream>
#include <vector>

enum class HTML_Type
{
	a, p, h1, h2
};

struct HTMLObject
{
	HTML_Type type; std::string on_click;
};

struct LanObject
{
	HTML_Type type; std::string on_click, id, text, style;

	std::string static type_toString(HTML_Type type)
	{
		if (type == HTML_Type::a) return "a";
		if (type == HTML_Type::p) return "p";
		if (type == HTML_Type::h1) return "h1";
		if (type == HTML_Type::h2) return "h2";
	}

	std::string getHTML()
	{
		std::string result;
		result += "<" + type_toString(type) + " id=" + id;
		if (on_click != "") result += " onclick='" + on_click + "'";
		if (style != "") result += " style='" + style + "'";
		if (type != HTML_Type::a) result += "></" + type_toString(type) + ">";
		else result += "/>";

		return result;
	}
};

struct func { std::string name; };

class Compiler
{
private:
public:
	std::vector<LanObject> objects; std::string title, general_script;
	std::vector<func> funcs;
	void compile_objectDefine(std::string line);
	void compile_privateFunction(std::string line);
	void compile_varDefining(std::string line);
	void compile_summonFunction(std::string line);

	void compile_function(std::string object_name, std::string func_name, std::string func_donng);
	void compile_var(std::string name, std::string value);

	bool isThat_privateFunction(std::string line);
	bool isThat_summonFunction(std::string line);

	void compile_line(std::string line);
	void compile(std::string file_path);

	void save_html(std::string path);
};