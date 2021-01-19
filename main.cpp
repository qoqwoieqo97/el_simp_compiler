#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Compiler.h"

int main(int argc, char *argv[])
{
	Lexer l("code.mc");
	if (!l.lexer()) std::cout << "ERROR CAUGHT:" << l.getError() << " at line:" << l.getLine() << std::endl;
	else
	{
		std::cout << "Lexering succesfully, starting to compile." << std::endl;
		Compiler c("code.mc");
		c.compile("compiled.cpp");
	}
	int i = 7;

	return 0;
}