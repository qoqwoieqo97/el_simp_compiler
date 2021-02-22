#pragma once
#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"

class Compiler
{
private:
	std::string javascript; std::string title; std::vector<ParsedLines> lines; int counter = 0;
public:
	Compiler(std::vector<ParsedLines>);
	std::string getFirstName(ParsedLines l);
		void CompileInFunc();
	void CompileFunc(ParsedLines l, int czn);
	void CompileLine(ParsedLines line);
	void Compile();

	void WriteToFile(std::string javascript_path);
};