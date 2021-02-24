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
	// def <-- getted
	// Next = func[.privFunc](param1,param2, ...) :
	// Explain lines will be named on this (up line)

	{ counter++; CONTROL_NEXT }
	/* Function Definition */
	if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT } /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name) // Getting -func-
	{
		counter++; CONTROL_NEXT
			if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT } /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyDot) // Controlling -privFunc-
		{
			{ counter++; CONTROL_NEXT }
			if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT } /* Blank Skipper */
			if (lines[line][counter].types == ParseType::name) { counter++; CONTROL_NEXT } // -privFunc-
		}
		if (lines[line][counter].types != ParseType::supkeyOpenBracket)
		{
			errs.push_back({ "SUPKEY_OPENBRACKET Syntax Error",GET_LINE });// If this invalid SUPKEY or type we will get error.
			return;
		}
		else
		{   // We getted Open Bracket sooo lets get parameters
			{ counter++; CONTROL_NEXT }
			if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT } /* Blank Skipper */
			if (lines[line][counter].types == ParseType::name)
			{
				{ counter++; CONTROL_NEXT }
				while (counter < lines[line].size())
				{
					if (lines[line][counter].types == ParseType::supkeyComo)
					{
						{ counter++; CONTROL_NEXT }
						if (lines[line][counter].types == ParseType::name) { counter++; CONTROL_NEXT }
						else {
							errs.push_back({ "Need NAME after como",GET_LINE });
							return;
						}
					}
					else if (lines[line][counter].types == ParseType::supkeyCloseBracket) // Closing After Variable
					{
						{ counter++; CONTROL_NEXT }
						break;
					}
					else
					{
						errs.push_back({ "Need SUPKEY_COMO or SUPKEY_CLOSEBRACKET",GET_LINE });
						return;
					}
				}
			}
			else if (lines[line][counter].types == ParseType::supkeyCloseBracket) // If direct close after open
			{
				{ counter++; CONTROL_NEXT }
			}
			else
			{
				errs.push_back({ "Need NAME or SUPKEY_CLOSEBRACKET",GET_LINE }); // If can't found any of this
				return;
			}

			// Endf
			if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT } /* Blank Skipper */
			if (lines[line][counter].types != ParseType::supkeyEndDef)
			{
				errs.push_back({ "Need SUPKEY_ENDEF at end of the function",GET_LINE }); // If can't found any of this
				return;
			}
		}
	}
	else
	{
		errs.push_back(Error({ "This should be text: " + lines[line][counter].value,GET_LINE }));
		return;
	}
}

void Lexer::Lex_summonFunction(Variable* var, int counter)
{
	if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name) // func(parameter <---
	{
		{ counter++; CONTROL_NEXT; }
		if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
		while (true)
		{
			if (lines[line][counter].types == ParseType::supkeyComo)
			{
				{ counter++; CONTROL_NEXT; }
				if (lines[line][counter].types == ParseType::name) // func(parameter,...,parameter <--
				{
					{ counter++; CONTROL_NEXT; }
				}
				else
				{
					errs.push_back({ "After SUPKEY_COMO should come NAME",line }); return; // func(parameter,...,? <--
				}
			}
			else if (lines[line][counter].types == ParseType::supkeyCloseBracket) // func(parmeter,...) <--
			{
				if (lines[line].size() != counter) errs.push_back({ "After ')' character should be empty.",line }); // func(...)        <--
				return;
			}
		}
	}
	else if (lines[line][counter].types == ParseType::supkeyCloseBracket) // func() <--
	{
		if (lines[line][counter].types == ParseType::blank) { counter++; } /* Blank Skipper */
		if (lines[line].size() != counter) errs.push_back({ "After ')' character should be empty.",line }); // func(...)        <--
		return;
	}
}

void Lexer::Lex_varCalculation(Variable* var, int counter)
{
	int bracket_counter = 0; bool text_input = false;
	if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
	while (lines[line].size()==counter)
	{
		if (lines[line][counter].types == ParseType::name)
		{
			counter++;
			{ counter++; CONTROL_NEXT; }
			if (lines[line].size() == counter)break;
			else if (lines[line][counter].types == ParseType::supkeyMathPlus || lines[line][counter].types == ParseType::supkeyMathNegat ||
				lines[line][counter].types == ParseType::supkeyMathMulti || lines[line][counter].types == ParseType::supkeyMathDivis)
			{
				counter++; CONTROL_NEXT;
			} // Should come something after math sign
		}
		else if (lines[line][counter].types == ParseType::supkeyTextInput) 
		{ 
			text_input = !text_input;
			if (text_input)
			{
				counter++;
				if (lines[line].size() != counter)
				{
					if (lines[line][counter].types == ParseType::supkeyMathPlus || 
						lines[line][counter].types == ParseType::supkeyMathNegat ||
						lines[line][counter].types == ParseType::supkeyMathMulti ||
						lines[line][counter].types == ParseType::supkeyMathDivis ||
						(bracket_counter>0&&lines[line][counter].types==ParseType::supkeyComo))
						{ counter++; CONTROL_NEXT; } // Should come after math signs something
					else { errs.push_back({ "After text should come SUPKEY_MATH or SUPKEY_COMO",GET_LINE }); return; }
				}
					
			}
			else { counter++; CONTROL_NEXT; } // Should come after a text_input = true
		}
		else if (lines[line][counter].types == ParseType::supkeyOpenBracket)bracket_counter++;
		else if (lines[line][counter].types == ParseType::supkeyCloseBracket)
			if (bracket_counter == 0) { errs.push_back({ "You haven't got any brackets to close",GET_LINE }); return; }
			else bracket_counter--;
		else if (lines[line][counter].types == ParseType::supkeyComo) { counter++; CONTROL_NEXT; };
	}
}

void Lexer::Lex_afterdotCalculation(Variable* var, int counter)
{
	if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name)
	{
		{ counter++; CONTROL_NEXT; }
		if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyOpenBracket)
		{
			{ counter++; CONTROL_NEXT; }

		}
		else if (lines[line][counter].types == ParseType::supkeyEqual)
		{
			{ counter++; CONTROL_NEXT; }
		}
		else
		{
			errs.push_back({ "Incorrect coming character after SUPKEY_DOT",GET_LINE });
			return;
		}

	}
	else
	{
		errs.push_back({ "After SUPKEY_DOT should come NAME",GET_LINE });
		return;
	}

}

void Lexer::Lex_line(Variable* var)
{
	if (lines[line].size() == 0)return;
	int counter = 0;
	if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
	if (lines[line][counter].types != ParseType::name) /* Controlling to be Name. If not we wll get err */
		errs.push_back(Error({ "First thing should be text not " + lines[line][counter].value , GET_LINE }));
	if (lines[line][counter].value == "def")
	{
		{ counter++; CONTROL_NEXT; }
		Lex_functionDefine(var, counter);
	}
	else
	{
		if (lines[line][counter].types == ParseType::blank) { counter++; CONTROL_NEXT; } /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyEqual) /* Controlling set variable */
		{
			counter++; CONTROL_NEXT;
			Lex_varCalculation(var, counter);

		}
		else if (lines[line][counter].types == ParseType::supkeyDot) /* Controlling private getting */
		{
			counter++; CONTROL_NEXT;
			Lex_summonFunction(var, counter);
		}
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