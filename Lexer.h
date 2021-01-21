#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum class Types
{
	STRING, INTEGER, FLOAT, VOID, NONE
};

struct Variable
{
	Types type; std::string value, name;
	Variable(Types t, std::string val, std::string name)
	{
		type = t; value = val; this->name = name;
	}
};

struct Function
{
	std::vector<Variable> param; std::string name; Types return_type;
	Function(std::string nm, Variable firstParam, Types return_t)
	{
		name = nm; param.push_back(firstParam); return_type = return_t;
	}
	Function(std::string nm, std::vector<Variable> params,Types return_t)
	{
		name = nm; param = params; return_type = return_t;
	}
	std::string gstring();
};

bool keyCodeC(std::string s, std::string control);
int hmint(std::string s, std::string control);
std::vector<std::string> cut(std::string string, std::string cutt);

class Lexer
{
private:
	std::fstream file; std::string error_string = "No error excepted."; int error_line = 0;
	std::vector<Function> funcs; std::vector<Variable> vars, inFunc_vars; Function in_func; bool isDefinedMain = false;
public:
	/// <summary>
	/// Simple Generator
	/// </summary>
	/// <param name="filePath"> File Path </param>
	Lexer(std::string filePath);
	~Lexer();

	/* Add function */
	void addFunction(Function func) { funcs.push_back(func); }

	/* TODO: Lexering Functions */

	/* Get Type */
	Types detectType(std::string type_segment);
	std::string static getValue(std::string type_segment, Types type);
	std::vector<Variable> lexer_type(std::string type_segment);

	/* Extern Lexer */
	bool lexer_extern(std::string extern_segment);

	/* BOOL Lexer */
	bool lexer_bool(std::string bool_segment);

	/* Variable Definition */
	bool static isThat_var_definition(std::string testsegment);
	bool lexer_var_definition(std::string var_segment);

	/* Function Definition */
	Variable lexer_parameter(std::string param);
	bool static isThat_func_definition(std::string testsegment);
	bool lexer_func_definition(std::string func_segment);

	/* Function */
	bool types_equal(std::vector<Variable> v, std::vector<Variable> v2);
	bool static isThat_func(std::string testsegment);
	bool weHaveThat_func(std::string name, std::string param);
	bool lexer_func(std::string func_segment);

	/* Return */
	bool lexer_return(std::string return_segment);

	/* IF Lexer */
	bool lexer_if(std::string ifsegment);

	/* Lexer Command Lexer like #lexer printvars */
	bool lexer_command(std::string command_segment);
	bool lexer_compiler_command(std::string command_segment);

	/* Lexer for one Line */
	bool lexer_line(std::string line_string);

	/* Simple Lexer While */
	bool lexer();

	/* Get error string. So that function will be return that std::string error_string at privates */
	std::string getError();

	/* If error caught that will be return error line. Or return 0 */
	int getLine();
};