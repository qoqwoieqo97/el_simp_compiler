#include <iostream>
#include "el_math.h"
/*USAGE DOWN*/
int main()
{
	elInt a = 984632, b=9876216,c=3232;
	std::cout << "a powers:" << std::endl;
	std::cout << a.powers();
	std::cout << std::endl << "b powers:" << std::endl;
	std::cout << b.powers();
	std::cout << std::endl << "c powers:" << std::endl;
	std::cout << c.powers();
	std::cout << std::endl << "result powers:" << std::endl;
	elInt result = a * b / c;
	std::cout << result.powers();
	std::cout << std::endl << "result integer:" << std::endl;
	std::cout << a * b / c;
}