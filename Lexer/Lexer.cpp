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

bool Lexer::skipBlank(int& counter)
{
	if (lines[line][counter].types == ParseType::blank)counter++;
	return control(counter, true);
}

bool Lexer::control(int& counter,bool nwte)
{
	if (lines[line].size() == counter)
	{
		if(!nwte) errs.push_back({ "Need something here. There is can't be end!",GET_LINE });
		return false;
	}return true;
}


bool Lexer::test(ParseType type, int&counter, bool nwte)
{
	if (!control(counter,true))
	{
		if(!nwte) errs.push_back({ "Controlling "+Parser::ptos(type)+" but next thing is not exist.",GET_LINE });
		return false;
	}
	else
	{
		if (lines[line][counter].types == type)
		{
			return true;
		}
		else
		{
			if(!nwte) errs.push_back({ "Required type " + Parser::ptos(type) + " is not here.",GET_LINE });
			return false;
		}
	}
}

void Lexer::Lex_functionDefine(Variable* var, int counter)
{
	// def <-- getted
	// Next = func[.privFunc](param1,param2, ...) :
	// Explain lines will be named on this (up line)

	{ counter++; CONTROL_NEXT }
	/* Function Definition */
	blanskip_if(counter) return; /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name) // Getting -func-
	{
		counter++; CONTROL_NEXT
			blanskip_if(counter) return; /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyDot) // Controlling -privFunc-
		{
			{ counter++; CONTROL_NEXT }
			blanskip_if(counter) return; /* Blank Skipper */
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
			blanskip_if(counter) return; /* Blank Skipper */
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
			blanskip_if(counter) return; /* Blank Skipper */
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
	blanskip_if(counter) return; /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name) // func(parameter <---
	{
		{ counter++; CONTROL_NEXT; }
		blanskip_if(counter) return; /* Blank Skipper */
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
					errs.push_back({ "After SUPKEY_COMO should come NAME",GET_LINE }); return; // func(parameter,...,? <--
				}
			}
			else if (lines[line][counter].types == ParseType::supkeyCloseBracket) // func(parmeter,...) <--
			{
				{ counter++; CONTROL_NEXT; }
				if (lines[line].size() != counter) errs.push_back({ "After ')' character should be empty.",GET_LINE }); // func(...)        <--
				return;
			}
		}
	}
	else if (test(ParseType::supkeyCloseBracket, counter)) // func() <--
	{
		blanskip_if(counter) return; /* Blank Skipper */
		counter++;
		if (lines[line].size() != counter) errs.push_back({ "After ')' character should be empty.",GET_LINE }); // func(...)        <--
		return;
	}
}

bool Lexer::Lex_var(Variable* var, int& counter)
{
	if (test(ParseType::name, counter,true))
	{
		{ counter++; }
		if (control(counter,true))
		{
			skipBlank(counter); if (!control(counter))return false;
			if (test(ParseType::supkeyOpenBracket,counter)) if (!Lex_inBrackets(var, counter)) return false;
		}
		else
		{
			errs.push_back({ "Bracket not closed.",GET_LINE }); return false;
		}
	}
	else if (lines[line][counter].types == ParseType::supkeyTextInput)
	{
		{counter++; if (!control(counter)) { errs.push_back({ "Need something after SUPKEY_TEXTINPUT",GET_LINE }); return false; } }

		if (lines[line][counter].types == ParseType::supkeyTextInput) { counter++;return true; }
		else if (lines[line][counter].types != ParseType::name) { errs.push_back({ "At starting of text input, second thing is such a wtf?",GET_LINE }); }
		else { counter++; if (!control(counter)) { errs.push_back({ "Need something after text input.", GET_LINE }); return false; } }

		if (lines[line][counter].types != ParseType::supkeyTextInput) { errs.push_back({ "SUPKEY_TEXTINPUT should be closed", GET_LINE }); return false; }
		{counter++; }
	}
	else { errs.push_back({ "First type is incorrect",GET_LINE }); return false; }
	return true;
}

bool Lexer::Lex_inBrackets(Variable* var, int &counter)
{
	int bracket_counter=0;
	counter++; if (!control(counter))return false;

	if (lines[line][counter].types == ParseType::supkeyCloseBracket)return true;
	else if (!Lex_var(var, counter)) return false;

	while (lines[line].size() > counter)
	{
		if (!skipBlank(counter)) { errs.push_back({ "Need something after BLANK",GET_LINE }); return false; }
		if (lines[line][counter].types == ParseType::supkeyMathPlus || lines[line][counter].types == ParseType::supkeyMathNegat ||
			lines[line][counter].types == ParseType::supkeyMathDivis || lines[line][counter].types == ParseType::supkeyMathMulti ||
			lines[line][counter].types == ParseType::supkeyComo)
		{
			counter++; if (!control(counter))return false;
			if (!skipBlank(counter)) { errs.push_back({ "Need something after BLANK",GET_LINE }); return false; }
			if (!Lex_var(var, counter)) return false;
		}
		else if (lines[line][counter].types == ParseType::supkeyCloseBracket) return true;
	}

	errs.push_back({ "Bracket not closed.",GET_LINE });
	return false;
}

void Lexer::Lex_varCalculation(Variable* var, int counter)
{
	int bracket_counter = 0; bool text_input = false;
	blanskip_if(counter) return; /* Blank Skipper */
	
	if (lines[line][counter].types == ParseType::name)
	{
		{ counter++; }
		if (lines[line].size() != counter && lines[line][counter].types == ParseType::supkeyOpenBracket)
		{
			/* Controlling in bracket */
			if (!Lex_inBrackets(var, counter)) return;
		}
	}/* Getting name */
	else if (lines[line][counter].types == ParseType::supkeyTextInput)
	{
		{ counter++; CONTROL_NEXT; }
		if (lines[line][counter].types != ParseType::name) { errs.push_back({ "Stupid Error, After SUPKEY_TEXTINPUT should be NAME",GET_LINE }); return; }
		else { counter++; CONTROL_NEXT; }
		if (lines[line][counter].types != ParseType::supkeyTextInput) { errs.push_back({ "You should close SUPKEY_TEXTINPUT" ,GET_LINE }); return; }
		else { counter++; }
	}/* Controlling --> "smthnghr" */
	else errs.push_back({ "Incorrect thing",GET_LINE });

	if (bracket_counter > 0)errs.push_back({ "Bracket not closed",GET_LINE });
}

void Lexer::Lex_afterdotCalculation(Variable* var, int counter)
{
	blanskip_if(counter) return; /* Blank Skipper */
	if (lines[line][counter].types == ParseType::name)
	{
		{ counter++; CONTROL_NEXT; }
		blanskip_if(counter) return; /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyOpenBracket)
		{
			{ counter++; CONTROL_NEXT; }
			Lex_summonFunction(var, counter);
		}
		else if (lines[line][counter].types == ParseType::supkeyEqual)
		{
			{ counter++; CONTROL_NEXT; }
			Lex_varCalculation(var, counter);
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
	blanskip_if(counter) return; /* Blank Skipper */
	if (lines[line][counter].types != ParseType::name) /* Controlling to be Name. If not we wll get err */
		errs.push_back(Error({ "First thing should be text not " + lines[line][counter].value , GET_LINE }));
	if (lines[line][counter].value == "def")
	{
		{ counter++; CONTROL_NEXT; }
		Lex_functionDefine(var, counter);
	}
	else if (lines[line][counter].value == "end")
	{
		counter++;
		if (lines[line].size() != counter)
		{
			blanskip_if(counter) return; /* Blank Skipper */
			if (lines[line].size() != counter) errs.push_back({ "END command not have any parameters",GET_LINE });
		}
	}
	else
	{
		{ counter++; CONTROL_NEXT; }
		blanskip_if(counter) return; /* Blank Skipper */
		if (lines[line][counter].types == ParseType::supkeyEqual) /* Controlling set variable */
		{
			counter++; CONTROL_NEXT;
			Lex_varCalculation(var, counter);

		}
		else if (lines[line][counter].types == ParseType::supkeyDot) /* Controlling private getting */
		{
			counter++; CONTROL_NEXT;
			Lex_afterdotCalculation(var, counter);
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