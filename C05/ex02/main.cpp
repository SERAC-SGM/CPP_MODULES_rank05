#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
	Bureaucrat b1("b1", 6);
	Bureaucrat b2("b2", 1);
	Bureaucrat b4("b4", 150);
	Bureaucrat b6("b6", 127);

	ShrubberyCreationForm f1("testfile");
	RobotomyRequestForm f2("target");
	PresidentialPardonForm f3("target");

	std::cout << "===== testing invalid exec (forms not signed) =====" << std::endl;
	std::cout << std::endl;
	std::cout << b1 << std::endl;
	b1.executeForm(f1);
	std::cout << f1 << std::endl;
	std::cout << std::endl;
	std::cout << b1 << std::endl;
	f2.execute(b1);
	std::cout << f2 << std::endl;
	std::cout << std::endl;
	std::cout << b1 << std::endl;
	f3.execute(b1);
	std::cout << f3 << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "===== signing forms =====" << std::endl;
	std::cout << std::endl;
	b1.signForm(f1);
	b2.signForm(f2);
	b2.signForm(f3);
	std::cout << std::endl;

	std::cout << "===== testing invalid exec (grade too low) =====" << std::endl;
	std::cout << std::endl;
	std::cout << b4 << std::endl;
	f1.execute(b4);
	std::cout << f1 << std::endl;
	std::cout << std::endl;
	std::cout << b6 << std::endl;
	f2.execute(b6);
	std::cout << f2 << std::endl;
	std::cout << std::endl;
	std::cout << b1 << std::endl;
	f3.execute(b1);
	std::cout << f3 << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "===== testing valid exec =====" << std::endl;
	std::cout << std::endl;
	b1.executeForm(f1);
	f2.execute(b2);
	b2.executeForm(f3);
	std::cout << std::endl;

	std::cout << "===== testing invalid exec (grade too low) =====" << std::endl;
	std::cout << std::endl;
	std::cout << b4 << std::endl;
	b4.executeForm(f1);
	std::cout << f1 << std::endl;
	std::cout << std::endl;
	std::cout << b4 << std::endl;
	f2.execute(b4);
	std::cout << f2 << std::endl;
	std::cout << std::endl;
	std::cout << b4 << std::endl;
	b4.executeForm(f3);
	std::cout << f3 << std::endl;
	std::cout << std::endl;

	//std::cout << std::endl;

	return (0);
}
