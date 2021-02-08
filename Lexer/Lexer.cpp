#include "Lexer.h"
#include "../Tools/line_breaker.h"
#include "../Tools/confirmer.h"
#include "../Tools/usefully.h"

std::ostream& operator<<(std::ostream&s, var_type t)
{
	if (t == var_type::NUMBER) s << "Number";
	else if (t == var_type::OBJECT) s << "Object";
	else if (t == var_type::TEXT) s << "Text";
	else if (t == var_type::NOT_DETECTED) s << "Not Detected";
	else s << "?";
	return s;
}

bool Lexer::is_starting_with(std::string t, std::string w, int start)
{
	for (int i = LB::get_textStarting(t,0); i < t.size() && i < w.size(); i++)
	{
		if (t[i] != w[i+start]) return false;
	}return true;
}

bool Lexer::control_lotOChars(std::string chars, std::string c_string)
{
	for (int i = 0,cI=0; i < chars.size(); i++)
	{
		if (cI >= c_string.size()) return false;
		for (; cI < c_string.size(); cI++) if (c_string[cI] == chars[i]) break;
	}
	return true;
}

int Lexer::control_lotOCharsI(std::string chars, std::string c_string)
{
	int i = 0, cI = 0;
	for (; i < chars.size(); i++)
	{
		if (cI >= c_string.size()) return -1;
		for (; cI < c_string.size(); cI++) if (c_string[cI] == chars[i]) break;
	}
	return cI;
}

bool Lexer::is_that_objectDefine(std::string d)
{
	bool c = control_lotOChars("{}->{}", d);
	return c;
}

bool Lexer::is_that_privateFunctionDefine(std::string d)
{
	bool starting = false;
	for (var v : variables) 
		if (is_starting_with(d, v.name, 0)) starting = true;
	if (!starting) return false;

	return control_lotOChars("()->{}", d);
}

bool Lexer::is_that_setVariable(std::string d)
{
	bool starting = false;
	for (var v : variables) if (is_starting_with(d, v.name, 0)) starting = true;
	for (var v : v_variables) if (is_starting_with(d, v.name, 0)) starting = true;
	if (!starting) return false;
	return control_lotOChars("=", d);
}

Lexer::line_type Lexer::get_lineType(std::string line)
{
	if (CON::is_empty(line)) return Lexer::line_type::EMPTY;
	else if (Lexer::is_starting_with("var", line, LB::get_textStarting(line))) return Lexer::line_type::VARIABLE_DEFINE;
	else if (Lexer::is_starting_with("function", line, LB::get_textStarting(line))) return Lexer::line_type::FUNCTION_DEFINE;
	else if (is_that_objectDefine(line)) return Lexer::line_type::OBJECT_DEFINE;
	else if (is_that_privateFunctionDefine(line)) return Lexer::line_type::FUNCTION_PRIVATE_DEFINE;
	else if (is_that_setVariable(line)) return Lexer::line_type::VARIABLE_SET;

	else return Lexer::line_type::NOT_DETECTED;
}

var_type Lexer::detect_type(std::string v)
{
	if (v[0] == '"' && v[v.size() - 1] == '"') return var_type::TEXT;
	else if (CON::is_int(v)) return var_type::NUMBER;
	else return var_type::NOT_DETECTED;
}



std::vector<ordered_error> Lexer::lex_defineVariable(std::string line, bool virtual_v)
{
	std::string name = "", value = ""; int counter = 0;
	for (int i = LB::get_textStarting(line,3); i < line.size(); i++)
	{
		if (counter == 0 && line[i] != ' ') name += line[i];
		else if (counter == 0 && line[i] == ' ')
		{
			i = LB::get_textStarting(line, i);
			if (line[i] != '=') return US::get_vector<ordered_error>(error_type::VAR_AFTERVARNAME_NOTDETECTED);
			i = LB::get_textStarting(line, i+1)-1;
			counter++;
		}

		else if (counter == 1) value += line[i];
	}
	if (counter == 1 && LB::isEmpty(value)) return US::get_vector<ordered_error>(error_type::VAR_VALUE_EMPTY);

	var_type type = detect_type(value);

	if (type == var_type::NOT_DETECTED) return US::get_vector<ordered_error>(error_type::VAR_VALUETYPE_UNDEFINED);
	if(virtual_v) v_variables.push_back(var(name, type));
	else variables.push_back(var(name, type));

	return US::get_vector<ordered_error>();
}

std::vector<ordered_error> Lexer::lex_setVariable(std::string d)
{
	std::string value;

	int i = 0;
	for (;; i++)
	{
		if (i >= d.size()) return US::get_vector<ordered_error>(error_type::VAR_AFTERVARNAME_NOTDETECTED);
		else if (d[i] == '=') break;
	}

	i = LB::get_textStarting(d, i + 1);
	for (; i < d.size(); i++) value += d[i];
	if (Lexer::detect_type(value) != var_type::NOT_DETECTED) return US::get_vector<ordered_error>();
	else return US::get_vector<ordered_error>(error_type::TYPE_NOTDETECTED);
}

std::vector<ordered_error> Lexer::lex_funcDoing(std::string top)
{
	std::vector<std::string> lines = LB::line_breaker(top);
	std::vector<ordered_error> result;
	for (std::string line : lines)
	{
		std::vector<ordered_error> er = lex_line(line,true);
		result.insert(result.end(), er.begin(), er.end());
	}
	return result;
}

std::vector<ordered_error> Lexer::lex_privateFunction(std::string d)
{
	function func;
	int f_Start = 0, variable_pos = 0;
	for (int i = 0; i < variables.size(); i++)
		if (is_starting_with(d, variables[i].name, 0)) { f_Start = variables[i].name.size(); variable_pos = i; break; }

	if (d[f_Start] != '.') return US::get_vector<ordered_error>(error_type::SYNTAX_ERROR);

	int i = f_Start + 1;

	for (; i < d.size(); i++)
		if (d[i] == '(') break;
		else func.name += d[i];

	i = control_lotOCharsI(")->{", d)+1;

	for (; i < d.size(); i++)
		if (d[i] == '}') break;
		else func.doing += d[i];
	
	variables[variable_pos].priv_funcs.push_back(func);
	v_variables = variables[variable_pos].in_vars;
	std::vector<ordered_error> result = lex_funcDoing(func.doing);
	variables[variable_pos].in_vars = v_variables;
	v_variables = std::vector<var>();

	return result;
}

std::vector<ordered_error> Lexer::lex_css(std::string s)
{
	return US::get_vector<ordered_error>();
}

std::vector<ordered_error> Lexer::lex_defineObject(std::string d)
{
	std::vector<var> inVars; std::string doing, css, name;
	int i = 0;
	for (; i < d.size(); i++)
	{
		if (d[i] == ' ') { i++; break; }
		else name += d[i];
	}
	i = LB::get_textStarting(d, i);
	if (d[i] != '{') return US::get_vector<ordered_error>(error_type::SYNTAX_ERROR);
	i++;
	for (; i < d.size(); i++)
	{
		if (d[i] == '}') { i++; break; }
		else css += d[i];
	}
	i = LB::get_textStarting(d, i);
	if (d[i] != '-' || d[i + 1] != '>') return US::get_vector<ordered_error>(error_type::SYNTAX_ERROR);
	i += 2;
	i = LB::get_textStarting(d, i);
	if(d[i]!='{') return US::get_vector<ordered_error>(error_type::SYNTAX_ERROR);
	i++;
	for (; i < d.size(); i++)
	{
		if (d[i] == '}') { i++; break; }
		else doing += d[i];
	}
	std::vector<ordered_error> result = lex_funcDoing(doing);
	inVars = v_variables; v_variables = std::vector<var>();
	var variable(name, var_type::OBJECT);
	variable.in_vars = inVars;
	variables.push_back(variable);
	return result;
}



std::vector<ordered_error> Lexer::lex_line(std::string line, bool virtual_v)
{
	Lexer::line_type type = get_lineType(line);
	if (type != Lexer::line_type::NOT_DETECTED)
	{
		if (type == Lexer::line_type::VARIABLE_DEFINE) return lex_defineVariable(line, virtual_v);
		else if (type == Lexer::line_type::VARIABLE_SET) return lex_setVariable(line);
		else if (type == Lexer::line_type::OBJECT_DEFINE) return lex_defineObject(line);
		else if (type == Lexer::line_type::FUNCTION_DEFINE);
		else if (type == Lexer::line_type::FUNCTION_PRIVATE_DEFINE) return lex_privateFunction(line);
		else if (type == Lexer::line_type::EMPTY) return US::get_vector<ordered_error>();
	}
	else return US::get_vector<ordered_error>(error_type::TYPE_NOTDETECTED);

	return US::get_vector<ordered_error>(error_type::LEXER_FAILED);
}


bool Lexer::lex_file(std::string file_path)
{
	bool is_thatError;
	std::fstream file(file_path);
	std::vector<std::string> lines = LB::line_breaker(LB::get_all(file));
	for (std::string line : lines)
	{
		for (ordered_error o : lex_line(line, false))errors.push_back(o);
	}
	return errors.size() == 0;
}