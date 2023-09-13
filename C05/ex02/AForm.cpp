#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string name, unsigned int gradeSign, unsigned int gradeExecute): _name(name), _signed(false), _requiredGradeSign(gradeSign), _requiredGradeExecute(gradeExecute)
{
	try
	{
		if (this->_requiredGradeExecute < 1 || this->_requiredGradeSign < 1)
		{
			throw std::string("AForm::GradeTooHighException");
		}
		else if (this->_requiredGradeExecute > 150 || this->_requiredGradeSign > 150)
			throw std::string("AForm::GradeTooLowException");
	} catch (std::string const &error)
	{
		std::cerr << error << std::endl;
	}
}

AForm::AForm(const AForm &toCopy): _requiredGradeSign(toCopy.getGradeSign()), _requiredGradeExecute(toCopy.getGradeExecute())
{
	*this = toCopy;
}

AForm::~AForm()
{}

AForm	&AForm::operator=(const AForm &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

const std::string	&AForm::getName() const
{
	return this->_name;
}

bool				AForm::isSigned() const
{
	return this->_signed;
}

unsigned int		AForm::getGradeSign() const
{
	return this->_requiredGradeSign;
}

unsigned int		AForm::getGradeExecute() const
{
	return this->_requiredGradeExecute;
}

void				AForm::beSigned(const Bureaucrat &bureaucrat)
{
	try
	{
		if (bureaucrat.getGrade() > this->getGradeSign())
			throw std::string("AAForm::GradeTooLowException");
	} catch (const std::string &error)
	{
		std::cerr << error << std::endl;
	}
	this->signForm(bureaucrat);
}

void				AForm::signForm(const Bureaucrat &bureaucrat)
{
	if (!this->isSigned())
	{
		std::cout << bureaucrat.getName() << " signed " << this->getName();
		this->_signed = true;
	}
	else
		std::cout << bureaucrat.getName() << " couldn't sign " << this->getName() << " because the form is already signed";
	if (bureaucrat.getGrade() < 1 || bureaucrat.getGrade() > 150)
		std::cout << bureaucrat.getName() << " couldn't sign " << this->getName() << " because its grade is invalid";
	else if (this->getGradeSign() < bureaucrat.getGrade())
		std::cout << bureaucrat.getName() << " couldn't sign " << this->getName() << " because its grade is too low";
	std::cout << std::endl;
}

std::ostream &operator << (std::ostream &flux, const AForm &object)
{
	flux << "Form " << object.getName();
	if (object.isSigned())
		flux << " is signed";
	else
		flux << " is not signed";
	flux << ", required grade to sign : " << object.getGradeSign();
	flux << ", required grade to execute: " << object.getGradeExecute();
	return flux;
}
