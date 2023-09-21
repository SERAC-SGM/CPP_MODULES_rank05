#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2 || !argv[1])
	{
		std::cout << "Invalid parameters" << std::endl;
		return 1;
	}
	try{
		PmergeMe test(argv[1]);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
