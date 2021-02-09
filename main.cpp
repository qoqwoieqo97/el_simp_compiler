#include "Lexer/Lexer.h"
#include "Compiler/Compiler.h"
#include "emils_lib-main/emils_lib.h"

void var_printer(var v, int counter = 0, std::string start_string="")
{
	std::cout << start_string << counter << ":" << v.name << ", " << v.type << std::endl;
	for (var v1 : v.in_vars)
	{
		var_printer(v1, counter + 1,start_string+" ");
	}
}

int main()
{
	Lexer lexer;
	lexer.lex_file("testing_code.fhtml");
	if (lexer.errors.size() > 0)
	{
		for (ordered_error er : lexer.errors) std::cout << er.toString() << std::endl;
		return -1;
	}
	else
	{
		Compiler compiler;
		compiler.compile("testing_code.fhtml");
		for (LanObject o : compiler.objects) std::cout << o.getHTML() << std::endl;
		compiler.save_html("index.html");
	}
	
	return 0;
}