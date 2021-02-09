#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

enum class error_type
{
	NONE, LEXER_FAILED, TYPE_NOTDETECTED, VAR_AFTERVARNAME_NOTDETECTED, VAR_VALUE_EMPTY, VAR_VALUETYPE_UNDEFINED,
	SYNTAX_ERROR
};

struct ordered_error
{
	error_type type; int line;
	ordered_error(error_type t, int l = 0) { type = t; line = l; }
	std::string toString() 
	{
		if (type == error_type::NONE) return std::to_string(line) + ": None";
		else if (type == error_type::TYPE_NOTDETECTED) return std::to_string(line) + ": Type not detected";
		else if (type == error_type::VAR_AFTERVARNAME_NOTDETECTED) return std::to_string(line) + ": At var defining after the name of variable has some syntax error.";
		else if (type == error_type::VAR_VALUE_EMPTY) return std::to_string(line) + ": Var value not entered.";
		else if (type == error_type::LEXER_FAILED) return std::to_string(line) + ": lexer failed.";
		else if (type == error_type::VAR_VALUETYPE_UNDEFINED) return std::to_string(line) + ": var's valuetype undefined";
		else if (type == error_type::SYNTAX_ERROR) return std::to_string(line) + ": Syntax Error";
		else return "?";
	}
	ordered_error* operator= (error_type t)
	{
		type = t;
		return this;
	}
};
enum class var_type { NOT_DETECTED, TEXT, NUMBER, OBJECT };
std::ostream& operator<<(std::ostream& s, var_type t);

struct function
{
	std::string name, doing, style, param;
};

struct var
{
	std::string name; var_type type; std::vector<function> priv_funcs; std::vector<var> in_vars;
	var(std::string n, var_type t) { name = n; type = t; }
};


class Lexer
{
public:
	std::vector<var> variables, v_variables; std::vector<ordered_error> errors;

	enum class line_type { 
		OBJECT_DEFINE, VARIABLE_DEFINE, VARIABLE_SET, FUNCTION_DEFINE, 
		FUNCTION_PRIVATE_DEFINE, FUNCTION_SUMMON, EMPTY, NOT_DETECTED };

	bool static is_starting_with(std::string this_string, std::string with_this_string, int start);

	bool static control_lotOChars(std::string chars, std::string c_string);
	int static control_lotOCharsI(std::string chars, std::string c_string);

	bool static is_that_objectDefine(std::string string);
	bool is_that_privateFunctionDefine(std::string string);
	bool is_that_summonFunction(std::string string);
	bool is_that_setVariable(std::string string);

	line_type get_lineType(std::string string);

	var_type static detect_type(std::string val);

	std::vector<ordered_error> lex_css(std::string s);



	/*LEXER*/
	std::vector<ordered_error> lex_defineVariable(std::string line, bool virtual_v);
	std::vector<ordered_error> lex_setVariable(std::string line);
	std::vector<ordered_error> lex_funcDoing(std::string top);
	std::vector<ordered_error> lex_privateFunction(std::string line);
	std::vector<ordered_error> lex_summonFunction(std::string line);
	std::vector<ordered_error> lex_defineObject(std::string line);
	std::vector<ordered_error> lex_line(std::string line,bool virtual_v);

	bool lex_file(std::string file_path);
};

