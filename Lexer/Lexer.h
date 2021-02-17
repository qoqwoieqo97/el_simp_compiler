#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define EMPTYS(x) std::vector<x>()
#define RETVEC(x,y) {std::vector<x> RETVEC_VARIABLE_DONTCHANGETHIS; RETVEC_VARIABLE_DONTCHANGETHIS.push_back(y); return RETVEC_VARIABLE_DONTCHANGETHIS;}
#define LEXER_EMPTYCOUNT 0
#define LEXER_FILLEDCOUNT 1

template <typename T>
struct Vector2 { T x, y; Vector2(T xx, T yy) { x = xx; y = yy; } Vector2() {} };
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

typedef std::vector<std::string> Strings;

enum class Type { VAR, HTML_OBJECT };
typedef std::vector<Type> Types;
// For variables and html objects
struct Function; struct Value; struct Error; struct Line;
typedef std::vector<Value> Values;
typedef std::vector<Values> DoubleValue;
typedef std::vector<Function> Functions;
typedef std::vector<Error> Errors;
typedef std::vector<Line> Lines;

struct Value { Type type; std::string name, start_value; Values priv_values; std::vector<Function> private_funcs; };

// Function Variable
struct Function { Types parameters; std::string name; Function(Types p, std::string n) { parameters = p; name = n; } };
struct Error { std::string error; int line; Error(std::string error_string, int ln = -1) { error = error_string; line = ln; } };
struct Line { std::string line; unsigned int line_c; };

enum class LineType { NotFound = 0, Empty, VarDefine, FuncDefine, SetVariable };
typedef LineType LT; // Shorter

class Lexer
{
private:
	// Useful structs

	struct StringAndError
	{
		std::string string; Errors errors;
	}; typedef StringAndError SAE;

	struct PrivateFunctionVariableName {
		// Name: function's owner variable's name
		std::string name, function_name, parameter; bool isThatHave; 
		PrivateFunctionVariableName(std::string n, std::string p, std::string fn, bool b)
		{ name = n; isThatHave = b; parameter = p; function_name=fn; }
	}; typedef PrivateFunctionVariableName PFVN;

	struct ParameterLexedResult {
		Error err; Strings parameters;
		ParameterLexedResult(Error e, Strings p) : err(e), parameters(p) {}
	}; typedef ParameterLexedResult PLR;

	struct LineSkipAndErrors
	{
		Errors err; int lineskip;
		LineSkipAndErrors(Errors e, int ls) : err(e), lineskip(ls) {}
	}; typedef LineSkipAndErrors LSAE;

	struct LexedVariable {
		std::string variable_name, variable_value;
		Errors errors;
	}; typedef LexedVariable LV;

	struct HTMLCreatorFunctionResult
	{
		std::string style, string; Errors errors;
	}; typedef HTMLCreatorFunctionResult HCFR;

public:
	Values vars; Functions public_functions;

	// Useful functions
	bool static isStartingWith(std::string thisString, std::string withThisString);
	int static isThatHave(std::string t_string, char controller);
	bool static isEmpty(std::string empty);
	Strings static cut(std::string string, char cutC);
	Strings static cut(std::string string, char cutC, std::string withoutThis);
	int static getInfo(Strings strings, int info);
	std::string static getWithNotEmpty(std::string str);
	int static getStringStarting(std::string str, int start = 0);
	std::string static delStartEmpty(std::string str, int start = 0);
	std::string static getBetween(std::string str, char c1, char c2);

	// Useful functions for Lexing
	int static isStartingWithVar(std::string line, Values var);
	int static findVariable(std::string name, Values vars);
	Vector2i static findVariable(std::string name, DoubleValue double_vars);
	Types static values2types(Values vl);
	Values static strings2values(Strings s);
	Errors static setEmptyLines(Errors er, int line);
	Errors static addLines(Errors er, int add);
	bool static isNotError(Errors er);
	Errors static getErrors(Error er);
	std::string static reverse(std::string s);
	std::string static removeStartEmpty(std::string s, int start = 0);
	std::string static removeStartAEndEmptys(std::string a);
	Strings static removeAllStartAEndEmptys(Strings strings);

	// Getting line type
	LT static get_LineType(std::string line, Values var);

	// Lexing
	// Lexing function
		// For controlling name of private variable
		PFVN static parse_functionName(std::string name);
		// For controlling parameter of function
		PLR static lex_parameters(std::string param);
		// Work in funcion                            Function Params, priv_values for owner variable
		int static work_inFunction(std::fstream* file, Values vals, Values params, Values &priv_values, Errors &res_er);
	LSAE static lex_functionDefinition(std::fstream *file, std::string line, Values &var, Functions &funcs);

	// Lexing var define
		// Parse varDefine
		LV static parse_varDefine(std::string var);
		// Detecting input type
		Type static detect_varType(std::string start_value);
		// Getting of " som et inh her e " or 654210+1 value
		SAE static getValue(std::string value, Values vals);
		// Constructing HTML
		HCFR static construct_html(std::string start_value, Values vals);
	Errors static lex_varDefine(std::string line, Values unchangableVar, Values& slot1, Values& slot2);

	// Public Lexing
	Lexer::LSAE static lex_line(std::fstream *file,std::string line, Values &vars, Functions &funcs);
	LSAE static lex_line_private(std::string line, Values vars, Values parameters, Values &priv_val);

	// File Lexing
	Errors lex_file(std::string file_path);
};