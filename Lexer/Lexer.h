#pragma once
#include "../Parser/Parser.h"
//MUSTNT
#define TEMP_USE_MAYBE 0
#define TEMP_USE_MUST 1

#define GET_LINE line+1
#define CONTROL_NEXT_F(lines,line,counter) if (lines[line].size() == counter) { errs.push_back({ "Required thing not here after '"+lines[line][counter-1].value+"'",GET_LINE }); return; }
#define CONTROL_NEXT CONTROL_NEXT_F(lines,line,counter)
#define CONTROL_NEXT_COUNTER {counter++;CONTROL_NEXT}
#define CONTROL_SELECTED_COUNTER(c) CONTROL_NEXT_F(lines,line,c)

#define R_CONTROL_NEXT_F(lines,line,counter) if (lines[line].size() != counter) { errs.push_back({ "This thing is not supposed to be here "+lines[line][counter-1].value,GET_LINE }); return; }
#define R_CONTROL_NEXT R_CONTROL_NEXT_F(lines,line,counter)

#define SKIP_BLANK(c) if (lines[line][c].types == ParseType::blank) { c++; CONTROL_NEXT; }

#define ret_iftrue(thing,ret) if(thing) return ret
#define blanskip_if(c) skipBlank(c); if (!control(c))

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

	bool skipBlank(int& counter);
	bool control(int& counter, bool not_write_to_errs=false);

	bool test(ParseType type, int& counter, bool nwte=false);

	// Lexing line function
		void Lex_functionDefine(Variable* var, int counter);
			bool Lex_var(Variable* var, int& counter);
			bool Lex_inBrackets(Variable* var, int &counter);
		void Lex_varCalculation(Variable* var, int counter);
		void Lex_summonFunction(Variable* var, int counter);
		void Lex_afterdotCalculation(Variable* var, int counter);
	void Lex_line(Variable* var);
	// Main lexer function
	bool Lex(Variable * var);


	/* Getting things */
	std::vector<Error> const getErrors() const;
};