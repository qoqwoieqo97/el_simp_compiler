#pragma once
#include "../Parser/Parser.h"
//MUSTNT
#define TEMP_USE_MAYBE 0
#define TEMP_USE_MUST 1


struct Function; 
struct Variable;

struct Variable
{
	std::string name; bool started = false; 
	std::vector<Function> funcs; std::vector<Variable> vars;
	Variable* getVar(std::string name);
	Function* getFunc(std::string name);
};

struct Function
{
	std::string name; std::vector<Variable> params;

};

struct Error
{
	std::string error; unsigned int line;
};



class Lexer
{
private:
	std::vector<ParsedLines> lines;
	Variable main;
	std::vector<Error> errs;
	unsigned int line;
public:
	Lexer(std::vector<ParsedLines> lns);

	// Lexing line function
		void Lex_functionDefine(Variable* var, int counter);
	void Lex_line(Variable* var);
	// Main lexer function
	bool Lex(Variable * var);


	/* Getting things */
	std::vector<Error> const getErrors() const;
};