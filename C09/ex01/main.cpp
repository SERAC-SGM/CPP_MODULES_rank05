#include <exception>
#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		return (1);
	}
	try{
		std::cout << RPN::evaluateRPN(argv[1]) << std::endl;
	} catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return (0);
}
