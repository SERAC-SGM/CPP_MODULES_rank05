#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &target): AForm("Presidential pardon", 25, 5), _target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &toCopy): AForm(toCopy)
{
	*this = toCopy;
}

PresidentialPardonForm::~PresidentialPardonForm()
{}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (!this->isSigned())
			throw std::string("PresidentialPardonForm::FormNotSignedException");
		if (this->getGradeExecute() < executor.getGrade())
			throw std::string("PresidentialPardonForm::GradeTooLowException");
	} catch (const std::string &error) {
		std::cerr << error << std::endl;
		return ;
	}
	std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
