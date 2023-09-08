#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "incorrect parameters";
		return (0);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}
