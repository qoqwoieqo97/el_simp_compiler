#include "Compiler.h"
Compiler::Compiler(std::vector<ParsedLines> input)
{
	lines = input; counter = 0;
}

void Compiler::CompileInFunc()
{
	for (; counter < lines.size(); counter++)
	{
		int in_lineCounter = 0;
		if (lines[counter][in_lineCounter].types == ParseType::blank) in_lineCounter++;
		if (lines[counter][in_lineCounter].value == "end")break;
		else
		{
			CompileLine(lines[counter]);
		}
	}
}

void Compiler::CompileFunc(ParsedLines line, int czn)
{
	czn++;
	if (line[czn].types == ParseType::blank)czn++;
	if (line[czn].types == ParseType::name) 
	{ 
		javascript += "function " + line[czn].value;
		czn++;
	}
	if (line[czn].types == ParseType::supkeyDot)
	{
		javascript += "_";
		czn++;
		if (line[czn].types == ParseType::name)
		{
			javascript += line[czn].value;
			czn++;
		}
	}
	if (line[czn].types == ParseType::supkeyOpenBracket)
	{
		javascript += "(";
		czn++;
	}
	while (true)
	{
		//Start of param
		if (line[czn].types == ParseType::blank)czn++;
		if (line[czn].types == ParseType::name)
		{
			javascript += line[czn].value;
			czn++;
		}

		if (line[czn].types == ParseType::blank)czn++;
		//Starting to new param
		if (line[czn].types == ParseType::supkeyComo) 
		{ 
			javascript += ",";
			czn++; 
			continue; 
		}
		//Closing params
		if (line[czn].types == ParseType::supkeyCloseBracket)
		{
			javascript += ")";
			czn++; 
			break;
		}
	}
	if (line[czn].types == ParseType::blank)czn++;
	if (line[czn].types == ParseType::supkeyEndDef)
	{
		javascript += "{";
		counter++;
		CompileInFunc();
		javascript += "}";
	}
}

void Compiler::CompileLine(ParsedLines line)
{
	if (line.size() == 0)return;

	int i = 0;
	if (line[i].types == ParseType::blank) i++;

	if (line[i].types == ParseType::name)
	{
		if (line[i].value == "def") CompileFunc(line, i);
	}
}

std::string Compiler::getFirstName(ParsedLines l)
{
	if (l[0].types == ParseType::blank) return l[1].value;
	else return l[0].value;
}

void Compiler::Compile()
{
	for (;counter<lines.size();counter++)
	{
		CompileLine(lines[counter]);
	}
}

void Compiler::WriteToFile(std::string javascript_path)
{
 	std::fstream file(javascript_path);
	file << javascript;
}