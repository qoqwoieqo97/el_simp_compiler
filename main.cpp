#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Compiler.h"

int main(int argc, char *argv[])
{
	Lexer l("code.mc");
	l.addFunction(Function("lib++", { Variable(Types::STRING,"","LibraryName") },Types::VOID));

	if (!l.lexer()) std::cout << "ERROR CAUGHT:" << l.getError() << " at line:" << l.getLine() << std::endl;
	else
	{
		std::cout << "Lexering succesfully, starting to compile." << std::endl;
		Compiler c("code.mc");
		c.compile("example_compile.cpp");
	}
	int i = 7;

	return 0;
}