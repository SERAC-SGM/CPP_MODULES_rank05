#include <exception>
#include <iostream>
#include <ostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1] == 0)
	{
		std::cerr << "Incorrect parameter" << std::endl;
		return 1;
	}
	try{
		BitcoinExchange	btc(argv[1]);
		btc.convert();
	} catch (const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
