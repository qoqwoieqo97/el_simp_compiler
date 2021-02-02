#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Compiler.h"

int main(int argc, char *argv[])
{
	Lexer l;
	l.addFunction(Function("lib++", { Variable(Types::STRING,"","LibraryName") }, Types::VOID));
	l.addFunction(Function("Display.draw", { Variable(Types::DRAWNING,"","Drawing Object") }, Types::VOID));
	l.addFunction(Function("Display.clear" , Types::VOID));

	if (!l.lexer("code.mc")) std::cout << "ERROR CAUGHT:" << l.getError() << " at line:" << l.getLine() << " in " << l.get_file() << std::endl;
	else
	{
		std::cout << "Lexering succesfully, starting to compile." << std::endl;
		Compiler c("example_compile.cpp");
		c.main_compile("code.mc");
	}
	int i = 7;
	std::string a;
	std::cin >> a;

	return 0;
}