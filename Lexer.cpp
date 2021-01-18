#include "Lexer.h"

bool stringController(std::string s, std::string control, int &i)
{
	int j = i;
	for (; j < s.size() && j-i < control.size(); j++)
	{
		if (s[j] != control[j - i]) return false;
	}
	i = j;
	return true;
}

bool keyCodeC(std::string s, std::string control)
{
	for (int i = 0; i < control.size(); i++) if (s[i] != control[i]) return false;
	return true;
}

std::string gat(std::string s, int a)
{
	std::string result = "";
	for (int i = a; i < s.size(); i++) result += s[i]; return result;
}
int hmint(std::string s, std::string control)
{
	int result = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (stringController(s, control, i)) result++;
	}
	return result;
}

std::vector<std::string> cut(std::string string, std::string cutt)
{
	std::vector<std::string> returner; std::string a = "";
	for (int i = 0; i < string.size(); i++)
	{
		if (stringController(string, cutt, i)) { returner.push_back(a); a = ""; i--; }
		else a += string[i];
	} returner.push_back(a);
	return returner;
}

std::string g(Types a)
{
	if (a == Types::STRING) return "string";
	else if (a == Types::INTEGER) return "integer";
	else if (a == Types::FLOAT) return "float";
	else return "none";
}

Types stt(std::string string)
{
	if (string == "string") return Types::STRING;
	else if (string == "integer" || string == "int") return Types::INTEGER;
	else if (string == "float") return Types::FLOAT;
	else return Types::NONE;
}

/*
* 
* 
*	*    ****  *   *  ****  ***
*	*    *      * *   *     *  *
*	*    ****    *    ****  ***
*	*    *      * *   *     *  *
*	*    *     *   *  *     *  *
*	**** **** *     * ****  *  *
* 
* 
*/

Lexer::Lexer(std::string filePath)
	:
	file(filePath) { }
Lexer::~Lexer() { file.close(); }


std::string Lexer::getError() { return error_string; }
int Lexer::getLine() { return error_line; }

bool Lexer::lexer_bool(std::string bool_segment)
{
	if (bool_segment == "true" || bool_segment == "false") return true;
	else if (hmint(bool_segment, "&&") > 0 || hmint(bool_segment, "||") > 0)
	{
		std::vector<std::string> cutted_segments = cut(bool_segment,"&&");
		std::vector<std::string> doubleCutted_segments;
		for (std::string segment : cutted_segments)
		{
			std::vector<std::string> cutting = cut(segment,"||");
			for (std::string c : cutting) doubleCutted_segments.push_back(c);
		}

		for (std::string segment : doubleCutted_segments) if (!lexer_bool(segment)) return false;
		return true;
	}
	else 
	{
		error_string = "Bool Segment '"; error_string += bool_segment; error_string += "' is not true bool segment.";
		return false;
	}
}

bool Lexer::lexer_if(std::string ifsegment)
{
	std::string bool_segment = "", if_command = ""; bool bs_detect = false, be_detect = false;
	for (int i = 0; i < ifsegment.size(); i++)
	{
		if (ifsegment[i] == ' ');
		else if (bs_detect && be_detect) if_command += ifsegment[i];
		else if (ifsegment[i] == '(')
		{
			bs_detect = true; i++;
			for (; i < ifsegment.size(); i++)
				if (ifsegment[i] == ')') { be_detect = true; if (!lexer_bool(bool_segment)) { return false; error_string = "If segment bool not detected."; } break; }
				else { bool_segment += ifsegment[i]; }
		}
		else
		{
			error_string = "";
			error_string += "'"; error_string += ifsegment[i]; error_string += "' character is not defined.";
			return false;
		}
	}
	if (!bs_detect) { error_string = "'(' not detected in if segment."; return false; }
	else if (!be_detect) { error_string = "')' not detected in if segment."; return false; }
	else return lexer_line(if_command);
}

std::vector<Types> Lexer::lexer_type(std::string type_segment)
{
	std::vector<std::string> type_segments = cut(type_segment, ","); std::vector<Types> wllReturn;
	for (std::string sgmnt : type_segments)
	{
		Types t = Types::NONE;
		for (int i = 0, j = 0; i < sgmnt.size(); i++)
		{
			if (sgmnt[i] == '"') j++;
			if (j > 1) t = Types::STRING;
		}
		if (t == Types::NONE)
		{
			for (int i = 0; i < sgmnt.size(); i++) if (sgmnt[i] == '.') t = Types::FLOAT;
			if (t == Types::NONE && sgmnt != "none") t = Types::INTEGER;
		}
		wllReturn.push_back(t);
	}
	return wllReturn;
}

bool Lexer::weHaveThat_func(std::string name, std::string param)
{
	for (auto func : funcs) if (name == func.name) {
		if (func.param == lexer_type(param)) return true; else {
			error_string = name + "(" + func.gstring() + ") named function's paramaters is wrong."; return false; } }
	error_string = "Can't found " + name +" named function";
	return false;
}

bool Lexer::lexer_func(std::string func_segment)
{
	std::string func_name = "", func_param; bool counter = false;
	for (int i = 0; i < func_segment.size(); i++)
	{
		if (func_segment[i] == ' ');
		else if (func_segment[i] == '(' && !counter) counter = true;
		else if (!counter) func_name += func_segment[i];
		else if (func_segment[i] == ')' && counter) break;
		else if (counter)func_param += func_segment[i];
	}
	if (weHaveThat_func(func_name, func_param)) return true;
	return false;
}

bool Lexer::isThat_func(std::string test_segment)
{
	bool counter = false;
	for (int i = 1; i < test_segment.size(); i++)
	{
		if (test_segment[i] == '(' && !counter) counter = true;
		else if (test_segment[i] == ')' && counter) return true;
	}
	return false;
}

bool Lexer::lexer_func_definition(std::string func_segment)
{
	std::string function_name, in_function, function_options, function_params; std::vector<Types> params; int counter = 0;
	for (int i = 0; i < func_segment.size(); i++)
	{
		if (func_segment[i] == ' ');
		else if (counter == 0 && func_segment[i] == '(') counter = 1;
		else if (counter == 0) function_name += func_segment[i];
		else if (counter == 1) for (; i < func_segment.size(); i++)
		{
			if (func_segment[i] == ' ');
			else if (func_segment[i] == ')') { counter = 2; break; }
			else function_params+=func_segment[i];
		}
		else if (counter == 2) for (; i < func_segment.size(); i++)
		{
			if (func_segment[i] == ' ');
			else if (func_segment[i] == ':') { counter = 3; break; }
			else function_options += func_segment[i];
		}
		else if (counter == 3)
		{
			if (func_segment[i] == ' ');
			else in_function += func_segment[i];
		}
	}

	if (counter == 0) { error_string = "Parameter starting error."; return false; }
	else if (counter == 1) { error_string = "Parameter ending error."; return false; }
	else if (counter == 2) { error_string = "Function options is not ended."; return false; }
	else if (in_function == "") { error_string = "In Function can't be empty."; return false; }

	/* Parameter */std::string f = "";
	for (int i = 0; i < function_params.size(); i++)
	{
		if (function_params[i] == ',') { params.push_back(stt(f)); f = ""; }
		else f += function_params[i];
	}
	params.push_back(stt(f));
	addFunction(Function(function_name, params));
	return lexer_line(in_function);
}

bool Lexer::isThat_func_definition(std::string test_segment)
{
	int counter = 0;
	for (int i = 1; i < test_segment.size(); i++)
	{
		if (test_segment[i] == '(' && counter == 0) counter = 1;
		else if (test_segment[i] == ')' && counter == 1) counter = 2;
		else if (test_segment[i] == ':' && counter == 2) return true;
	}
	return false;
}

bool Lexer::lexer_extern(std::string extern_segment)
{
	std::string extern_string = ""; bool getted_type = false; std::string type = "NOTYPE";
	for (int i = 6; i < extern_segment.size(); i++)
	{
		if(getted_type) extern_string += extern_segment[i];
		else
		{
			if (stringController(extern_segment, "C++", i)) { type = "C++"; i--; getted_type = true; }
			else if (stringController(extern_segment, "C", i)) { type = "C"; i--; getted_type = true; }
		}
	}
	if (!getted_type) { error_string = "Extern Type Not Getted"; return false; }
	std::cout << "Extern saw Type:" << type << " Externing:" << extern_string << std::endl;
	return true;
}

bool Lexer::lexer_line(std::string line_string)
{
	if (keyCodeC(line_string, "extern")) return lexer_extern(line_string);
	else if (hmint(line_string, ";") > 0 && hmint(line_string,"extern ") == 0) { for (auto a : cut(line_string, ";")) if (!lexer_line(a)) return false; return true; }
	else if (keyCodeC(line_string, "if")) return lexer_if(gat(line_string, 2));
	else if (keyCodeC(line_string, "while")) return lexer_if(gat(line_string, 5));
	else if (isThat_func_definition(line_string)) return lexer_func_definition(line_string);
	else if (isThat_func(line_string)) return lexer_func(line_string);
	else if (keyCodeC(line_string, "//") || keyCodeC(line_string, "//")) return true;
	else { error_string = "That command is unknown: " + line_string; return false; }
}

bool Lexer::lexer()
{
	std::string line_string; int lineCounter = 0;
	while (std::getline(file, line_string))
	{
		lineCounter++;
		if (!lexer_line(line_string)) { error_line = lineCounter; return false; }
	}
	return true;
}