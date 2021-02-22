#include "Lexer.h"

/* Struct functions */
Variable* Variable::getVar(std::string name)
{
	for (int i = 0; i < vars.size(); i++) if (vars[i].name == name)return&vars[i];
	return nullptr;
}

Function* Variable::getFunc(std::string name)
{
	for (int i = 0; i < funcs.size(); i++) if (funcs[i].name == name)return&funcs[i];
	return nullptr;
}

/* Lexer */

Lexer::Lexer(std::vector<ParsedLines> lns)
{
	lines = lns; line = 0;
}

void Lexer::Lex_functionDefine(Variable* var, int counter)
{
	counter++;
	/* Function Definition */
	if (lines[line][counter].types == ParseType::blank) counter++; /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name)
	{
		counter++;
		if (lines[line][counter].types == ParseType::blank) counter++; /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyDot)
		{
			counter++;
			if (lines[line][counter].types == ParseType::blank) counter++; /* Blank Skipper */
			if (lines[line][counter].types == ParseType::name)counter++;
		}
		if (lines[line][counter].types != ParseType::supkeyOpenBracket)
		{
			errs.push_back({ "SUPKEY_OPENBRACKET Syntax Error",line });
			return;
		}
		else
		{
			counter++;
			if (lines[line][counter].types == ParseType::blank) counter++; /* Blank Skipper */
			if (lines[line][counter].types == ParseType::name)
			{
				counter++;
				while (counter < lines[line].size())
				{
					if (lines[line][counter].types == ParseType::supkeyComo)counter++;
					else if (lines[line][counter].types == ParseType::supkeyCloseBracket)
					{
						counter++;
						break;
					}
					else
					{
						errs.push_back({ "Need SUPKEY_COMO or SUPKEY_CLOSEBRACKET",line });
						return;
					}
				}
			}
			else if (lines[line][counter].types == ParseType::supkeyCloseBracket)
			{
				counter++;
			}
			else
			{
				errs.push_back({ "Need NAME or SUPKEY_CLOSEBRACKET",line });
				return;
			}
		}
	}
	else
	{
		errs.push_back(Error({ "This should be text: " + lines[line][counter].value,line }));
		return;
	}
}

void Lexer::Lex_line(Variable* var)
{
	int counter = 0;
	if (lines[line][counter].types == ParseType::blank) counter++; /* Blank Skipper */
	if (lines[line][counter].types != ParseType::name) /* Controlling to be Name. If not we wll get err */
		errs.push_back(Error({ "First thing should be text not " + lines[line][counter].value , line}));
	else if (lines[line][counter].value == "def")
	{
		Lex_functionDefine(var, counter);
	}
}

bool Lexer::Lex(Variable * var)
{
	for (; line < lines.size(); line++)
	{
		Lex_line(var);
	}
	return errs.size() != 0;
}

/* Getting Things */
std::vector<Error> const Lexer::getErrors() const
{
	return errs;
}