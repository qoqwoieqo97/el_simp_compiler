#include <iostream>
#include <fstream>
#include "Lexer.h"

int main(int argc, char *argv[])
{
	Lexer l("code.mc");
	Function f("sqrt", Types::INTEGER); f.param.push_back(Types::INTEGER);
	l.addFunction(Function("print", Types::STRING)); l.addFunction(f);
	if (!l.lexer()) std::cout << "ERROR CAUGHT:" << l.getError() << " at line:" << l.getLine() << std::endl;
	else std::cout << "Lexering succesfully" << std::endl;
	int i = 7;

	return 0;
}