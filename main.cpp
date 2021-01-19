#include <iostream>
#include <fstream>
#include "Lexer.h"

int main(int argc, char *argv[])
{
	Lexer l("code.mc");
	if (!l.lexer()) std::cout << "ERROR CAUGHT:" << l.getError() << " at line:" << l.getLine() << std::endl;
	else std::cout << "Lexering succesfully" << std::endl;
	int i = 7;

	return 0;
}