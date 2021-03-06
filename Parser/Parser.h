#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#ifndef SUPKEY_BLANK_STYLE
#define SUPKEY_BLANK_STYLE ' '
#endif

#ifndef SUPKEY_SUPKEYDOT_STYLE
#define SUPKEY_SUPKEYDOT_STYLE '.'
#endif

#ifndef SUPKEY_CLOSEBRACKET_STYLE
#define SUPKEY_CLOSEBRACKET_STYLE ')'
#endif

#ifndef SUPKEY_OPENBRACKET_STYLE
#define SUPKEY_OPENBRACKET_STYLE '('
#endif

#ifndef SUPKEY_ENDDEF_STYLE
#define SUPKEY_ENDDEF_STYLE ':'
#endif

#ifndef SUPKEY_COMO_STYLE
#define SUPKEY_COMO_STYLE ','
#endif

#ifndef SUPKEY_TEXTINPUT_STYLE
#define SUPKEY_TEXTINPUT_STYLE '"'
#endif

#ifndef SUPKEY_EQUAL_STYLE
#define SUPKEY_EQUAL_STYLE '='
#endif

#ifndef SUPKEY_MATH_PLUS_STYLE
#define SUPKEY_MATH_PLUS_STYLE '+'
#endif

#ifndef SUPKEY_MATH_NEGAT_STYLE
#define SUPKEY_MATH_NEGAT_STYLE '-'
#endif

#ifndef SUPKEY_MATH_MULTI_STYLE
#define SUPKEY_MATH_MULTI_STYLE '*'
#endif

#ifndef SUPKEY_MATH_DIV_STYLE
#define SUPKEY_MATH_DIV_STYLE '/'
#endif

enum class ParseType
{
	key,
	name,
	supkeyDot,
	supkeyOpenBracket,
	supkeyCloseBracket,
	supkeyEndDef,
	supkeyComo,
	supkeyTextInput,
	supkeyEqual,
	supkeyMathPlus,
	supkeyMathNegat,
	supkeyMathMulti,
	supkeyMathDivis,
	blank
};
struct ParsedLine
{
	ParseType types;
	std::string value;
};
typedef std::vector<ParsedLine> ParsedLines;

class Parser
{
public:
			ParseType static charToPT(char n, bool &intext);
		ParsedLines static parse(std::string n);
	std::vector<ParsedLines> static parse_file(std::string path);
};