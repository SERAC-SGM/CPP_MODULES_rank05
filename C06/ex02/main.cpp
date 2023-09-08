#include <ctime>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv)
{
	srand(time(0));

	if (argc > 1 && argv)
	{
		cerr << "command-line arguments aren't supported" << endl;
		return EXIT_FAILURE;
	}
	Base *c;
	
	cout << "TEST 1" << endl;
	c = Base::generate();

	cout << endl;
	Base::identify(c);
	Base::identify(*c);

	delete c;
	return EXIT_SUCCESS;

	return (0);
}
