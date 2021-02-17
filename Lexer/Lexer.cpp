#include "Lexer.h"

bool Lexer::isStartingWith(std::string th, std::string wt)
{
	for (int i = 0; i < th.size() && i < wt.size(); i++)
	{
		if (th[i] != wt[i]) return false;
	}return true;
}

int Lexer::isThatHave(std::string ts, char c)
{
	int counter = 0;
	for (char ch : ts) if (ch == c) counter++; return counter;
}

bool Lexer::isEmpty(std::string t)
{
	for (char c : t) if (c != ' ' && c != '\t') return false;
	return true;
}

Strings Lexer::cut(std::string string, char cutC)
{
	Strings result;
	std::string peach;
	for (char c : string)
	{
		if (c == cutC)
		{
			result.push_back(peach); peach = "";
		}
		else peach += c;
	} result.push_back(peach);
	return result;
}

Strings Lexer::cut(std::string string, char cutC, std::string wThis)
{
	auto isThereAny = [](std::vector<bool> controlling)
	{
		for (int i = 0; i < controlling.size(); i++) if (controlling[i]) return true;
		return false;
	};

	Strings result;
	std::string peach;
	std::vector<bool> b; for (int i = 0; i < wThis.size(); i++) b.push_back(false);

	for (char c : string)
	{
		for (int i = 0; i < wThis.size(); i++) if (c == wThis[i]) b[i] = !b[i];
		if (c == cutC)
		{
			if (!isThereAny(b))
			{
				result.push_back(peach); peach = "";
			}
			else peach += c;
		}
		else peach += c;
	} result.push_back(peach);
	return result;
}

int Lexer::getInfo(Strings strings, int info)
{
	if (info == LEXER_EMPTYCOUNT)
	{
		int counter = 0;
		for (std::string string : strings)
			if (isEmpty(string)) counter++;
		return counter;
	}
	else if (info == LEXER_FILLEDCOUNT)
	{
		int counter = 0;
		for (std::string string : strings)
			if (!isEmpty(string)) counter++;
		return counter;
	}
	else return -1;
}

std::string Lexer::getWithNotEmpty(std::string str)
{
	std::string res;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ' && str[i] != '\t')res += str[i];
	}return res;
}

int Lexer::getStringStarting(std::string str, int strt)
{
	for (int i = strt; i < str.size(); i++)
	{
		if (str[i] != ' ' && str[i] != '\t') return i;
	}
	return str.size();
}

std::string Lexer::delStartEmpty(std::string str, int strt)
{
	std::string result;
	for (int i = getStringStarting(str, strt); i < str.size(); i++)
	{
		result += str[i];
	}return result;
}

std::string Lexer::getBetween(std::string str, char c1, char c2)
{
	bool t = false; std::string result;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == c1) t = true;
		else if (str[i] == c2) t = false;
		else if (t) result += str[i];
	}
	return result;
}

/* Lexer */
int Lexer::isStartingWithVar(std::string line, Values var)
{
	for (int i = 0; i < var.size(); i++)
	{
		if (isStartingWith(line, var[i].name)) return i; // Returning true array position
	}return -1; // Or return -1 for not found
}

int Lexer::findVariable(std::string name, Values var)
{
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i].name == name)return i;
	}return -1; // Not found
}

Vector2i Lexer::findVariable(std::string name, DoubleValue double_vars)
{
	for (int i = 0; i < double_vars.size(); i++)
	{
		for (int j = 0; j < double_vars[i].size(); j++)
		{
			if (double_vars[i][j].name == name) return { i,j };
		}
	}
	return { -1,-1 };
}

Types Lexer::values2types(Values v)
{
	Types result;
	for (int i = 0; i < v.size(); i++)
	{
		result.push_back(v[i].type);
	}return result;
}

Values Lexer::strings2values(Strings s)
{
	Values result;
	for (std::string a : s) result.push_back({ Type::VAR, a, "", Values() });
	return result;
}

Errors Lexer::setEmptyLines(Errors er, int line)
{
	for (int i = 0; i < er.size(); i++) if (er[i].line == -1) er[i].line = line;
	return er;
}

Errors Lexer::addLines(Errors er, int add)
{
	for (int i = 0; i < er.size(); i++) er[i].line += add; return er;
}

bool Lexer::isNotError(Errors er)
{
	for (int i = 0; i < er.size(); i++)
	{
		if (er[i].error != "") return false;
	}return true;
}

Errors Lexer::getErrors(Error er)
{
	RETVEC(Error, er);
}

std::string Lexer::reverse(std::string a)
{
	std::string result;
	for (int i = a.size() - 1; i >= 0; i--)result += a[i]; return result;
}

std::string Lexer::removeStartEmpty(std::string a, int start)
{
	std::string result;
	for (int i = getStringStarting(a, start); i < a.size(); i++) result += a[i]; return result;
}

std::string Lexer::removeStartAEndEmptys(std::string a)
{
	a = removeStartEmpty(a);
	a = reverse(a); a = removeStartEmpty(a); return reverse(a);
}

Strings Lexer::removeAllStartAEndEmptys(Strings strings)
{
	for (int i = 0; i < strings.size(); i++)
		strings[i] = removeStartAEndEmptys(strings[i]);
	return strings;
}

LT Lexer::get_LineType(std::string line, Values var)
{
	if (isEmpty(line)) return LT::Empty; // Empty Lines
	int starting_var = isStartingWithVar(line, var); // If not found that function will return -1
	if (starting_var != -1)
	{
		if (line[var[starting_var].name.size()] == '.' && isStartingWith(line, "def"))// Controlling for private functions like button.onClick()
			return LT::FuncDefine;
		else if (isThatHave(line, '=') == 1)return LT::SetVariable;
	}
	else if (isStartingWith(line, "def"))// def key is importent for function defining. So just we need controlling def in start
	{
		return LT::FuncDefine;
	}
	else if (isThatHave(line, '=') == 1)// controlling variable = 5
	{
		return LT::VarDefine;
	}
	return LT::NotFound; // Lexer failed there
}

// Lexing function
Lexer::PFVN Lexer::parse_functionName(std::string name)
{
	if (isThatHave(name, '.') == 1)
	{
		std::string var_name, func_name, parameter; int i = 4;
		for (; i < name.size(); i++)
			if (name[i] == '.') break;
			else var_name += name[i];/* Getting variable name */ i++;
		for (; i < name.size(); i++)
			if (name[i] == ' ' || name[i] == '(') break;
			else func_name += name[i]; /* Getting function name */ i++;
		for (; i < name.size(); i++)
			if (name[i] == ')') break;
			else parameter += name[i]; /* Getting function parameters */ i++;
		return PFVN(var_name, parameter, func_name, true); // return results
	}
	else if (isThatHave(name, '.') == 0)
	{
		std::string func_name, parameter; int i = 4;
		for (; i < name.size(); i++)
			if (name[i] == ' ' || name[i] == '(') break;
			else func_name += name[i]; /* Getting function name */ i++;
		for (; i < name.size(); i++)
			if (name[i] == ')') break;
			else parameter += name[i]; /* Getting function parameters */ i++;
		return PFVN("", parameter, func_name, false); // return results
	}
	return PFVN("", "", "", false); // returning non private function for now
}

Lexer::PLR Lexer::lex_parameters(std::string param)
{
	Strings breaked = cut(param, ','); // Cutting parameters by ,
	PLR res(Error(""), Strings()); // Result
	for (std::string oneOBreaked : breaked)
		// if like that = " para meter, param eter " give error
		if (getInfo(cut(oneOBreaked, ' '), LEXER_FILLEDCOUNT) > 1) return PLR(Error("Parameter syntax error."), Strings());
	// if not like = " parameter, parameter2 " add to res
		else res.parameters.push_back(getWithNotEmpty(oneOBreaked));
	return res;
}

int Lexer::work_inFunction(std::fstream* file, Values vals, Values params, Values& pValues, Errors& result)
{
	std::string nline; int skip_lines = 0;
	while (std::getline(*file, nline))
	{
		skip_lines++;
		nline = delStartEmpty(nline);
		if (nline == "end") break;

		LSAE ls = lex_line_private(nline, vals, params, pValues);
		ls.err = addLines(ls.err, skip_lines);
		result.insert(result.end(), ls.err.begin(), ls.err.end());
		// Adding every errors to result variable
		//for (int i = 0; i < ls.lineskip && std::getline(*file, nline); i++) skip_lines++;
	}
	return skip_lines;
}

Lexer::LSAE Lexer::lex_functionDefinition(std::fstream* file, std::string line, Values& var, Functions& funcs)
{
	Lexer::PFVN pfvn = parse_functionName(line); Errors result;

	if (isThatHave(pfvn.name, ' ') || isThatHave(pfvn.function_name, ' '))
		result.push_back(Error("Can't use ' ' (empty line) in name."));
	else if (pfvn.function_name == "")
	{
		// Detecting error
		if (isThatHave(line, '.') > 1) result.push_back(Error("There is too many dots"));
	}

	int location = findVariable(pfvn.name, var);// Var location
	// if variable not found
	if (location == -1 && pfvn.isThatHave)
		result.push_back(Error(pfvn.function_name + "'s private variable " + pfvn.name + " not found."));

	PLR parmRes = lex_parameters(pfvn.parameter); // Lexing parameters
	if (parmRes.err.error != "") result.push_back(parmRes.err); // If error is not empty returning error

	Values val_params = strings2values(parmRes.parameters); // Getting parameters for type Value

	/* End for errors. Now Lexing function doings */

	Values private_values = pfvn.isThatHave && location != -1 ? var[location].priv_values : Values(); // Getting private values
	int skipped_lines = work_inFunction(file, var, val_params, private_values, result);

	Types prmTypes = values2types(val_params); // Converting values to types for function define
	if (result.size() > 0) return LSAE(result, skipped_lines); // If have errors we will dont add function

	/* Adding functions */
	if (pfvn.isThatHave && location != -1)
	{
		// Adding to private variable
		var[location].priv_values = private_values;
		var[location].private_funcs.push_back(Function(prmTypes, pfvn.function_name));
	}
	else
	{
		// Adding to public functions
		funcs.push_back(Function(prmTypes, pfvn.function_name));
	}
	//END
	return LSAE(result, skipped_lines);
}

// Lexing Var


Lexer::LV Lexer::parse_varDefine(std::string var)
{
	Strings peachs = cut(var, '=');
	LV result; result.variable_name = removeStartAEndEmptys(peachs[0]);
	result.variable_value = removeStartAEndEmptys(peachs[1]);

	// Name Error Detecting
	{
		int counter = 0;
		Strings strs = cut(result.variable_name, ' ');
		for (int i = 0; i < strs.size(); i++)
		{
			if (getWithNotEmpty(strs[i]) != "") counter++;
		}if (counter > 1) result.errors.push_back(Error("Name parsed by ' ' characters."));
	}

	return result;
}

Type Lexer::detect_varType(std::string name)
{
	if (isStartingWith(name, "HTML")) return Type::HTML_OBJECT;
	else return Type::VAR;
}

Lexer::SAE Lexer::getValue(std::string value, Values vals)
{
	Strings parsedByPlus = removeAllStartAEndEmptys(cut(value, '+', "\""));
	std::string result; Errors errors;
	for (int i = 0; i < parsedByPlus.size(); i++)
	{
		int ddCounter = isThatHave(parsedByPlus[i], '"');
		if (ddCounter == 0)
		{
			int loc = findVariable(parsedByPlus[i], vals);
			if (loc != -1) result += vals[loc].start_value;
			else errors.push_back(Error("Variable " + parsedByPlus[i] + " not found."));
		}
		else if (ddCounter == 2)
		{
			for (int j = 1; j < parsedByPlus[i].size() - 1; j++)
			{
				result += parsedByPlus[i][j];
			}
		}
	}
	return { result ,errors };
}

Lexer::HCFR Lexer::construct_html(std::string start_value, Values vals)
{
	HCFR result;
	std::string parameters = getBetween(start_value, '(', ')');
	Strings parsed_pars = removeAllStartAEndEmptys(cut(parameters, ',', "\""));
	std::vector<SAE> objects;
	for (int i = 0; i < parsed_pars.size(); i++)
	{
		SAE s = getValue(parsed_pars[i], vals);
		objects.push_back(s);
		if (s.errors.size() > 0)
		{
			result.errors.insert(result.errors.end(), s.errors.begin(), s.errors.end());
		}
	}
	if (objects.size() != 2) result.errors.push_back(Error("Constructor doesnt have 2 parameter"));
	else
	{
		result.string = objects[0].string;
		result.style = objects[1].string;
	}
	return result;
}

Errors Lexer::lex_varDefine(std::string line, Values uv, Values& s1, Values& s2)
{
	line = removeStartEmpty(line);
	LV lexed_var = parse_varDefine(line); Type var_type = detect_varType(lexed_var.variable_value);
	lexed_var.variable_name = removeStartAEndEmptys(lexed_var.variable_name);
	Vector2i locationVector;
	{
		DoubleValue doubleValue;
		//doubleValue.push_back(uv);
		doubleValue.push_back(s1);
		doubleValue.push_back(s2);
		locationVector = findVariable(lexed_var.variable_name, doubleValue);
	}

	//if (locationVector.x != -1)
	//	if (locationVector.x == 0) lexed_var.errors.push_back(Error("You can't set out of function variable."));

	if (var_type == Type::HTML_OBJECT)
	{
		Values all_values; all_values.insert(all_values.end(), s1.begin(), s1.end()); 
		all_values.insert(all_values.end(), s2.begin(), s2.end());

		HCFR constructed = construct_html(lexed_var.variable_value, all_values);
		if (constructed.errors.size() > 0) return constructed.errors;
		if (locationVector.x == 0) s1[locationVector.y].start_value = constructed.string;
		else if (locationVector.x == 1) s2[locationVector.y].start_value = constructed.string;
		else if (locationVector.x == -1)
		{
			Value val; val.name = lexed_var.variable_name;
			val.start_value = constructed.string;
			val.type = var_type;
			s1.push_back(val);
		}
	}
	else if (var_type == Type::VAR)
	{
		Values av;
		av.insert(av.end(), uv.begin(), uv.end());
		av.insert(av.end(), s1.begin(), s1.end());
		av.insert(av.end(), s2.begin(), s2.end());
		SAE compiled_string = getValue(lexed_var.variable_value, av);
		if (compiled_string.errors.size() > 0) 
			lexed_var.errors.insert(lexed_var.errors.end(), 
				compiled_string.errors.begin(), compiled_string.errors.end());
		else
		{
			std::string constructed_string = compiled_string.string;
			if (locationVector.x == 0) s1[locationVector.y].start_value = constructed_string;
			else if (locationVector.x == 1) s2[locationVector.y].start_value = constructed_string;
			else if (locationVector.x == -1)
			{
				Value val; val.name = lexed_var.variable_name;
				val.start_value = constructed_string;
				val.type = var_type;
				s1.push_back(val);
			}
		}
	}

	if (lexed_var.errors.size() > 0)return lexed_var.errors;
	return Errors();
}

Lexer::LSAE Lexer::lex_line(std::fstream* file, std::string line, Values& vars, Functions& funcs)
{
	LT type = get_LineType(line, vars);
	if (type == LT::NotFound) return LSAE(getErrors(Error("Lexer failed, line type not found.")), 0);
	else if (type == LT::FuncDefine) return lex_functionDefinition(file, line, vars, funcs);
	else if (type == LT::VarDefine || type == LT::SetVariable)
	{
		Values emptyVal;
		return LSAE(lex_varDefine(line, Values(), vars, emptyVal), 0);
	}
	else if (type == LT::Empty) return LSAE(Errors(), 0);
	return LSAE(getErrors(Error("Lexer failed, line type found but line not lexed.")), 0);
}

Lexer::LSAE Lexer::lex_line_private(std::string line, Values vars, Values params, Values& priv_vals)
{
	LT type;
	{
		Values topVals = priv_vals; topVals.insert(topVals.end(), vars.begin(), vars.end());
		type = get_LineType(line, topVals);
	}
	if (type == LT::NotFound) return LSAE(getErrors(Error("Lexer failed, line type not found dri.")), 0);
	else if (type == LT::VarDefine || type == LT::SetVariable)
		return LSAE(lex_varDefine(line, vars, priv_vals, params), 0);
	else if(type ==LT::FuncDefine) return LSAE(getErrors(Error("You cant define a function in function.")), 0);
	return LSAE(getErrors(Error("BRRRRRRRRRRUH")), 0);
}

Errors Lexer::lex_file(std::string file_path)
{
	// Opening file and creating std::string line for std::getline(string,string)
	std::fstream file(file_path); std::string line; int line_Counter = 0;
	// Result array for return
	Errors result;
	while (std::getline(file, line))
	{
		line_Counter++;
		// Adding errors line by line
		LSAE ls = lex_line(&file, line, vars, public_functions);
		ls.err = addLines(ls.err, line_Counter + 1);
		result.insert(result.end(), ls.err.begin(), ls.err.end());
		if (ls.lineskip > 0)
		{
			line_Counter += ls.lineskip;
		}
	}
	// Returning calculated errors
	return result;
}