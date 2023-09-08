#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat b1("b1", 5);
	Bureaucrat b2("b2", 1);
	Bureaucrat b4("b4", 150);
	Bureaucrat b6("b6", 145);

	std::cout << "===== invalid bureaucrat initialization =====" << std::endl;
	std::cout << std::endl;
	Bureaucrat b5("b5", 157);
	std::cout << b5 << std::endl;
	Bureaucrat b3("b3", 0);
	std::cout << b3 << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing decrementation =====" << std::endl;
	std::cout << std::endl;
	std::cout << "init : " << b6 << std::endl;
	for (int i = 0; i < 10; i++)
	{
		b6.decrementGrade();
		std::cout << b6 << std::endl;
	}
	std::cout << "end : " << b6 << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing incrementation =====" << std::endl;
	std::cout << std::endl;
	std::cout << "init : " << b1 << std::endl;
	for (int i = 0; i < 10; i++)
	{
		b1.incrementGrade();
		std::cout << b1 << std::endl;
	}
	std::cout << "end : " << b1 << std::endl;
	std::cout << std::endl;

	return (0);
}
