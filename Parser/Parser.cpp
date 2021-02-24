#include "Parser.h"

ParseType Parser::charToPT(char n, bool &intext)
{
	if (!intext)
	{
		if (n == SUPKEY_BLANK_STYLE || n == '\t')return ParseType::blank;
		else if (n == SUPKEY_SUPKEYDOT_STYLE) return ParseType::supkeyDot;
		else if (n == SUPKEY_OPENBRACKET_STYLE) return ParseType::supkeyOpenBracket;
		else if (n == SUPKEY_CLOSEBRACKET_STYLE) return ParseType::supkeyCloseBracket;
		else if (n == SUPKEY_COMO_STYLE) return ParseType::supkeyComo;
		else if (n == SUPKEY_ENDDEF_STYLE) return ParseType::supkeyEndDef;
		else if (n == SUPKEY_EQUAL_STYLE) return ParseType::supkeyEqual;
		else if (n == SUPKEY_MATH_PLUS_STYLE)return ParseType::supkeyMathPlus;
		else if (n == SUPKEY_MATH_NEGAT_STYLE)return ParseType::supkeyMathNegat;
		else if (n == SUPKEY_MATH_MULTI_STYLE)return ParseType::supkeyMathMulti;
		else if (n == SUPKEY_MATH_DIV_STYLE)return ParseType::supkeyMathDivis;
	}
	if (n == SUPKEY_TEXTINPUT_STYLE) { intext = !intext; return ParseType::supkeyTextInput; }
	else return ParseType::name;
}

ParsedLines Parser::parse(std::string n)
{
	if (n == "") return ParsedLines();
	bool intext = false;
	ParseType now=charToPT(n[0],intext);
	std::string ram; ParsedLines s;
	for (char c : n)
	{
		ParseType res = charToPT(c, intext);
		if (res != now || res==ParseType::supkeyOpenBracket || res==ParseType::supkeyDot ||
			res == ParseType::supkeyCloseBracket || res==ParseType::supkeyComo ||
			res == ParseType::supkeyEndDef || res==ParseType::supkeyTextInput ||
			res == ParseType::supkeyMathPlus || res == ParseType::supkeyMathNegat ||
			res == ParseType::supkeyMathMulti || res == ParseType::supkeyMathDivis )
		{
			s.push_back({now,ram});
			ram = c;
			now = res;
		}
		else ram += c;
	}
	s.push_back({ now,ram });
	if (s.size() == 1 && s[0].types == ParseType::blank) return ParsedLines();
	return s;
}

std::vector<ParsedLines> Parser::parse_file(std::string path)
{
	std::fstream file; file.open(path);
	if (!file.is_open())
	{
		std::cout << "Unable to open file" << std::endl;
		return std::vector<ParsedLines>();
	}
	std::string line_str; std::vector<ParsedLines> result;
	while (std::getline(file, line_str))
	{
		result.push_back(parse(line_str));
	}
	return result;

}