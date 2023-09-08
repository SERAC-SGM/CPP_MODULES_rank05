#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &target): AForm("Robotomy request", 72, 45), _target(target)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &toCopy): AForm(toCopy)
{
	*this = toCopy;
}

RobotomyRequestForm::~RobotomyRequestForm()
{}

RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (!this->isSigned())
		{
			throw std::string("RobotomyRequestForm::FormNotSignedException");
			return ;
		}
		if (this->getGradeExecute() < executor.getGrade())
		{
			throw std::string("RobotomyRequestForm::GradeTooLowException");
			return ;
		}
	} catch (const std::string &error) {
		std::cerr << error << std::endl;
		return ;
	}
	std::cout << "* drilling noises * ";
	if (std::time(0) % 2)
	{
		std::cout << this->_target << " has been robotomized successfully" << std::endl;
		return;
	}
	else {
		std::cout << "the robotomy failed" << std::endl;
	}

}
