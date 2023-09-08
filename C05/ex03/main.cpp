#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main()
{
	{
		Bureaucrat b("b", 1);
		Intern someRandomIntern;
		AForm* rrf;
		AForm* rrf2;

		rrf = someRandomIntern.makeForm("Robotomy request", "Bender");
		rrf2 = someRandomIntern.makeForm("Robotomy rsadgdsfsbequest", "Bender");

		rrf->beSigned(b);
		rrf->execute(b);

		delete rrf;
	}
	return (0);
}
