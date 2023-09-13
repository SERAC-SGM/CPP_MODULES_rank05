#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	Bureaucrat b1("b1", 5);
	Bureaucrat b2("b2", 1);
	Bureaucrat b4("b4", 150);
	Bureaucrat b6("b6", 145);

	Form f1("f1", 3, 10);
	Form f4("f4", 3, 10);
	Form f5("f5", 145, 10);

	std::cout << std::endl;
	std::cout << "===== invalid form initialization =====" << std::endl;
	Form f2("f2", 0, 10);
	std::cout << f2 << std::endl;
	std::cout << std::endl;
	Form f3("f3", 4, 160);
	std::cout << f3 << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing valid sign grade =====" << std::endl;
	std::cout << b2 << std::endl;
	b2.signForm(f1);
	std::cout << f1 << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing double sign grade =====" << std::endl;
	b2.signForm(f1);
	std::cout << std::endl;

	std::cout << "===== testing invalid sign grade (too low) =====" << std::endl;
	std::cout << b1 << std::endl;
	b1.signForm(f4);
	std::cout << f4 << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing invalid sign grade (invalid grade) =====" << std::endl;
	Bureaucrat b7("b7", 155);
	std::cout << b7 << std::endl;
	b7.signForm(f5);
	std::cout << f5 << std::endl;
	std::cout << std::endl;

	return (0);
}
