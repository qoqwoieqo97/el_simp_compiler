#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum class Types
{
	STRING, INTEGER, FLOAT, NONE
};

struct Function
{
	std::vector<Types> param; std::string name;
	Function(std::string nm, Types firstParam)
	{
		name = nm; param.push_back(firstParam);
	}
	Function(std::string nm, std::vector<Types> params)
	{
		name = nm; param = params;
	}
	std::string gstring()
	{
		std::string returner = "";
		for (Types s : param)
		{
			if (s == Types::STRING) returner+= ",string";
			else if (s == Types::INTEGER) returner += ",integer";
			else if (s == Types::FLOAT) returner += ",float";
			else returner += ",none";
		}
		return returner;
	}
};

class Lexer
{
private:
	std::fstream file; std::string error_string = "No error excepted."; int error_line = 0;
	std::vector<Function> funcs;
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
	std::vector<Types> lexer_type(std::string type_segment);

	/* Extern Lexer */
	bool lexer_extern(std::string extern_segment);

	/* BOOL Lexer */
	bool lexer_bool(std::string bool_segment);

	/* Function Definition */
	bool isThat_func_definition(std::string testsegment);
	bool lexer_func_definition(std::string func_segment);

	/* Function */
	bool isThat_func(std::string testsegment);
	bool weHaveThat_func(std::string name, std::string param);
	bool lexer_func(std::string func_segment);

	/* IF Lexer */
	bool lexer_if(std::string ifsegment);

	/* Lexer for one Line */
	bool lexer_line(std::string line_string);

	/* Simple Lexer While */
	bool lexer();

	/* Get error string. So that function will be return that std::string error_string at privates */
	std::string getError();

	/* If error caught that will be return error line. Or return 0 */
	int getLine();
};