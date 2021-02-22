#include <iostream>
#include "Lexer/Lexer.h"
#include "Compiler/Compiler.h"
#include "Parser/Parser.h"

std::ostream& operator<<(std::ostream& s, ParseType t)
{
	if (t == ParseType::blank) s << "Blank";
	else if (t == ParseType::key) s << "Key";
	else if (t == ParseType::name) s << "Name";
	else if (t == ParseType::supkeyDot) s << "Supkey Dot";
	else if (t == ParseType::supkeyOpenBracket) s << "Supkey Open Bracket";
	else if (t == ParseType::supkeyCloseBracket) s << "Supkey Close Bracket";
	else if (t == ParseType::supkeyEndDef) s << "Supkey End Def";
	else if (t == ParseType::supkeyComo) s << "Supkey Como";
	return s;
}
int main()
{
	Parser par;
	std::vector<ParsedLines> types = par.parse_file("testing_code.fhtml");

	Lexer lexer(types);
	Variable main_var;
	/* Lexer dont founds error */
	if(!lexer.Lex(&main_var))
	{
		Compiler comp(types);
		comp.Compile();
		comp.WriteToFile("javascriptresult.js");
	}
	/* Lexer founds error */
	else
	{
		std::cout << "LEX_ERROR:" << std::endl;
		const std::vector<Error> result = lexer.getErrors();
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << 
				result[i].error << " in line: " << result[i].line 
				<< std::endl;
		}
	}
	return 0;
}