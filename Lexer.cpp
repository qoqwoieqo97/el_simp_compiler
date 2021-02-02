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
	else if (a == Types::DRAWNING) return "drawning";
	else if (a == Types::VOID) return "void";
	else return "none";
}

Types stt(std::string string)
{
	if (string == "string") return Types::STRING;
	else if (string == "integer" || string == "int") return Types::INTEGER;
	else if (string == "float") return Types::FLOAT;
	else if (string == "void") return Types::VOID;
	else if (string == "drawning") return Types::DRAWNING;
	else return Types::NONE;
}

bool isNumber(char c)
{
	if (c == '0') return true;
	else if (c == '1') return true;
	else if (c == '2') return true;
	else if (c == '3') return true;
	else if (c == '4') return true;
	else if (c == '5') return true;
	else if (c == '6') return true;
	else if (c == '7') return true;
	else if (c == '8') return true;
	else if (c == '9') return true;
	else return false;
}

bool isNumber(std::string s)
{
	for (char c : s) if (!isNumber(c)) return false; return true;
}

std::string Function::gstring()
{
	std::string returner = "";
	for (Variable var : param)
	{
		returner += g(var.type) + " " + var.name + ",";
	}
	return returner;
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

Lexer::Lexer()
	: in_func("", Variable(Types::NONE, "", ""),Types::NONE) { }


std::string Lexer::getError() { return error_string; }
int Lexer::getLine() { return error_line; }
std::string Lexer::get_file() { return error_file; }

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

std::string Lexer::getValue(std::string type_segment,Types type)
{
	if (type == Types::STRING)
	{
		std::string val = "";
		for (int i = 1; i < type_segment.size() - 1; i++) val += type_segment[i];
		return val;
	}
	else if (type == Types::FLOAT || type == Types::INTEGER) return type_segment;
	else return "";
}
Types Lexer::detectType(std::string type_segment)
{
	int nod = hmint(type_segment, ".");
	if (type_segment[0] == '"' && type_segment[type_segment.size() - 1] == '"') return Types::STRING;
	else if (nod > 0 && nod < 0) return Types::FLOAT;
	else if (isNumber(type_segment)) return Types::INTEGER;
	else
	{
		for (auto var : vars) if (var.name == type_segment) return var.type;
		return Types::NONE;
	}
}

std::vector<Variable> Lexer::lexer_type(std::string type_segment)
{
	if (type_segment == "")
	{
		std::vector<Variable> empty;
		return empty;
	}
	std::vector<std::string> type_segments = cut(type_segment, ","); std::vector<Variable> wllReturn;
	for (std::string sgmnt : type_segments)
	{
		bool finded = false;
		for (Variable a : vars)
		{
			if (sgmnt == a.name) { wllReturn.push_back(Variable(a.type, a.value, a.name)); finded = true; break; }
		}
		for (Variable a : inFunc_vars)
		{
			if (sgmnt == a.name) { wllReturn.push_back(Variable(a.type, a.value, a.name)); finded = true; break; }
		}
		if (!finded)
		{
			Types t = detectType(sgmnt);
			if (t != Types::NONE) wllReturn.push_back(Variable(t, getValue(sgmnt, t), "none"));
		}
	}
	return wllReturn;
}

bool Lexer::types_equal(std::vector<Variable> v, std::vector<Variable> v2)
{
	if (v.size() != v2.size()) return false;
	else for (int i = 0; i < v.size(); i++) 
	{ 
		if (v[i].type != v2[i].type) return false;
	}
	return true;
}

bool Lexer::weHaveThat_func(std::string name, std::string param)
{
	for (auto func : funcs) if (name == func.name) {
		if (types_equal(func.param, lexer_type(param))) return true;
		else { error_string = name + "(" + func.gstring() + ") named function's paramaters is wrong."; return false; } }

	
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

Variable Lexer::lexer_parameter(std::string param)
{
	std::vector<std::string> cutted = cut(param, " ");
	if (cutted.size() != 2) { error_string = "Function parameter syntax is wrong."; return Variable(Types::NONE, "", ""); }
	return Variable(stt(cutted[0]), "", cutted[1]);
}

bool Lexer::lexer_func_definition(std::string func_segment)
{
	std::string function_name, in_function, function_options, function_params; int counter = 0; bool p_start = false, p_end = false, f_end = false;
	for (int i = 0; i < func_segment.size(); i++)
	{
		if (counter == 0)
		{
			if (func_segment[i] == '(') { counter = 1; p_start = true; }
			else if (func_segment[i] == ' ');
			else function_name += func_segment[i];
		}
		else if (counter == 1)
		{
			if (func_segment[i] == ')') { counter = 2; p_end = true; }
			else function_params += func_segment[i];
		}
		else if (counter == 2)
		{
			if (func_segment[i] == ':') { counter = 3; i++; f_end = true; }
			else if (func_segment[i] == ' ');
			else function_options += func_segment[i];
		}
		else if (counter == 3)
		{
			in_function += func_segment[i];
		}
	}

	if (!p_start) { error_string = "Parameter starting error."; return false; }
	else if (!p_end) { error_string = "Parameter ending error."; return false; }
	else if (!f_end) { error_string = "Function options is not ended."; return false; }
	else if (in_function == "") { error_string = "In Function can't be empty."; return false; }

	std::vector<Variable> params;
	if (function_params != "")
	{
		/* Parameter */std::string f = "";
		for (int i = 0; i < function_params.size(); i++)
		{
			if (function_params[i] == ',')
			{
				if (lexer_parameter(f).type != Types::NONE) { params.push_back(lexer_parameter(f)); f = ""; }
				else return false;
			}
			else f += function_params[i];
		}
		if (lexer_parameter(f).type != Types::NONE) { params.push_back(lexer_parameter(f)); f = ""; }
		else return false;
	}

	if (function_options != "int" && function_options != "string" && function_options != "float" && function_options!="void")
	{
		error_string = "Parameter isn't excepted"; return false;
	}
	if (function_name == "main")
	{
		if (isDefinedMain)
		{
			error_string = "There can be only 1 main defining. main(): or #compiler main.  You defined second main with main():";
			return false;
		}
		isDefinedMain = true;
	}
	inFunc_vars = params; in_func = Function(function_name, params, stt(function_options));
	addFunction(Function(function_name, params,stt(function_options)));
	return lexer_line(in_function);
}

bool Lexer::isThat_func_definition(std::string test_segment)
{
	int counter = 0; char c[3] = { '(',')',':' };
	for (int i = 1; i < test_segment.size(); i++)
	{
		if (test_segment[i] == c[counter]) counter++;
		if (counter > 2) return true;
	}
	return false;
}

bool Lexer::lexer_return(std::string return_segment)
{
	std::string return_var;
	for (int i = 7; i < return_segment.size(); i++)
	{
		return_var += return_segment[i];
	}
	if (detectType(return_var) == in_func.return_type)return true;
	else 
	{
		if (isDefinedMain) return true;
		else if (in_func.return_type == Types::NONE)
		{
			error_string = "U are not in the function";
		}
		else error_string = "Function return type is invalid, should be " + g(in_func.return_type);
		return false;
	}
}

bool Lexer::isThat_var_definition(std::string testsegment)
{
	return hmint(testsegment, "int")>0 || hmint(testsegment, "string")>0 || hmint(testsegment, "float")>0 || hmint(testsegment,"drawning")>0;
}

bool Lexer::lexer_var_definition(std::string var_segment)
{
	bool y = false; int st = 0; Types t = Types::NONE;
	if (keyCodeC(var_segment, "int ")) { y = true; st = 4; t = Types::INTEGER; }
	else if (keyCodeC(var_segment, "string ")) { y = true; st = 7; t = Types::STRING; }
	else if (keyCodeC(var_segment, "float ")) { y = true; st = 6; t = Types::FLOAT; }
	else if (keyCodeC(var_segment, "drawning ")) { y = true; st = 9; t = Types::DRAWNING; }
	int parsing = 0; std::string varname = ""; std::string value = ""; bool not_take = false;

	for (int i = st; i < var_segment.size(); i++)
	{
		if (!not_take && var_segment[i] == ' ');
		else if (parsing == 0) 
		{ 
			if (var_segment[i] == '=') parsing++; else varname += var_segment[i];
		}
		else if (var_segment[i] == '"' && parsing == 1) not_take = !not_take;
		else if (parsing == 1) value += var_segment[i];
	}
	if (varname == "") { error_string = "Variable name cant be empty..."; return false; }
	else if (parsing == 1) { if (value == "") { error_string = "Variable value cant be empty..."; return false; }}
	vars.push_back(Variable(t, value, varname));
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
	return true;
}

bool Lexer::lexer_command(std::string command_segment)
{
	bool cr = false;
	std::vector<std::string> commands = cut(command_segment, " ");
	for (int i = 0; i < commands.size(); i++)
	{
		if (commands[i] == "#lexer") continue;
		else if (commands[i] == "printvars")
		{
			std::cout << "Request: Printing Readed Variables" << std::endl;
			for (Variable var : vars) std::cout << "Name:" << var.name << " Type:" << g(var.type) << " Value:" << var.value << std::endl;
			cr = true;
		}
		else if (commands[i] == "printfuncs")
		{
			std::cout << "Request: Printing Readed Functions" << std::endl;
			for (Function f : funcs) std::cout << "Name:" << f.name << "(" << f.gstring() << ") " << std::endl;
			cr = true;
		}
		else
		{
			error_string = "#lexer Unknown command " + commands[i]; return false;
		}
	}
	if (!cr) error_string = "Lexer can't get any command.";
	return cr;
}

bool Lexer::lexer_compiler_command(std::string command_segment)
{
	std::string command;
	for (int i = 10; i < command_segment.size(); i++)
	{
		command += command_segment[i];
	}
	if (command == "main")
	{
		if (isDefinedMain)
		{
			error_string = "There can be only 1 main defining. main(): or #compiler main. You defined second main with #compiler";
			return false;
		}
		else { isDefinedMain = true; return true; }
	}
	error_string = "What is that compiler command:" + command;
	return false;
}

bool Lexer::lexer_load(std::string c)
{
	std::string path = "";
	for (int i = 5; i < c.size(); i++)
	{
		path += c[i];
	}

	std::fstream control_file(path);
	if (!control_file.is_open())
	{
		error_string = "Can't open " + path;
		return false;
	}

	return lexer(path);
}

bool Lexer::lexer_line(std::string line_string)
{
	if (keyCodeC(line_string, "//") || keyCodeC(line_string, "empty") || line_string == "") return true;
	else if (keyCodeC(line_string, "#lexer")) return lexer_command(line_string);
	else if (keyCodeC(line_string, "#compiler")) return lexer_compiler_command(line_string);
	else if (keyCodeC(line_string, "load")) return lexer_load(line_string);
	else if (keyCodeC(line_string, "extern") || keyCodeC(line_string, " extern")) return lexer_extern(line_string);
	else if (hmint(line_string, ";") > 0 && hmint(line_string, "extern ") == 0 && !isThat_func_definition(line_string)) { for (auto a : cut(line_string, ";")) if (!lexer_line(a)) return false; return true; }
	else if (keyCodeC(line_string, "if")) return lexer_if(gat(line_string, 2));
	else if (keyCodeC(line_string, "while")) return lexer_if(gat(line_string, 5));
	else if (keyCodeC(line_string, "return")) return lexer_return(line_string);
	else if (isThat_func_definition(line_string)) return lexer_func_definition(line_string);
	else if (isThat_func(line_string)) return lexer_func(line_string);
	else if (isThat_var_definition(line_string)) return lexer_var_definition(line_string);
	else { error_string = "That command is unknown: " + line_string; return false; }
}

bool Lexer::lexer(std::string file_path)
{
	std::fstream file(file_path);
	std::string line_string; int lineCounter = 0;
	while (std::getline(file, line_string))
	{
		lineCounter++;
		std::vector<Variable> n; inFunc_vars = n; in_func = Function("", Variable(Types::NONE, "", ""),Types::NONE);
		if (!lexer_line(line_string)) { error_line = lineCounter; error_file = file_path; return false; }
	}
	return true;
}