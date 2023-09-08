#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern()
{}

Intern::Intern(const Intern &toCopy)
{
	*this = toCopy;
}

Intern::~Intern()
{}

Intern	&Intern::operator=(const Intern &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

AForm	*Intern::makeForm(const std::string &formName, const std::string &target) const
{
	std::string	formNames[3] = {"Robotomy request", "Presidential pardon", "Shrubbery creation"};
	AForm		*forms[3] = {new RobotomyRequestForm(target), new PresidentialPardonForm(target), new ShrubberyCreationForm(target)};
	AForm		*formCreated = NULL;

	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			formCreated = forms[i];
		}
		else {
			delete forms[i];
		}
	}
	if (formCreated == NULL)
		std::cout << "Can't create form : " << formName << " does not exist" << std::endl;
	return formCreated;
}
