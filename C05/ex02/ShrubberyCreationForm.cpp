#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target): AForm("Shrubbery creation", 145, 137), _target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &toCopy): AForm(toCopy)
{
	*this = toCopy;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (!this->isSigned())
			throw std::string("ShrubberyCreation::FormNotSignedException");
		if (this->getGradeExecute() < executor.getGrade())
			throw std::string("ShrubberyCreationForm::GradeTooLowException");
	} catch (const std::string &error) {
		std::cerr << error << std::endl;
		return ;
	}
	std::ofstream outfile((this->_target + "_shrubbery").c_str());
	outfile << "ASCII tree" << std::endl;
}
