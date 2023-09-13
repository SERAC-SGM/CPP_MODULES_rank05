#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(const std::string &name, unsigned int grade): _name(name), _grade(grade)
{
	try
	{
		if (this->_grade < 1)
		{
			throw std::string("Bureaucrat::GradeTooHighException");
		}
		else if (this->_grade > 150)
			throw std::string("Bureaucrat::GradeTooLowException");
	} catch (std::string const &error)
	{
		std::cerr << error << std::endl;
	}
}

Bureaucrat::Bureaucrat(const Bureaucrat &toCopy)
{
	*this = toCopy;
}

Bureaucrat::~Bureaucrat()
{}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

const std::string	&Bureaucrat::getName() const
{
	return this->_name;
}

unsigned int		Bureaucrat::getGrade() const
{
	return this->_grade;
}

void				Bureaucrat::incrementGrade()
{
	try
	{
		if (this->_grade <= 1 || this->_grade >= 150)
			throw std::string("Bureaucrat::GradeTooHighException");
		else
			this->_grade--;
	} catch (std::string const &error)
	{
		std::cerr << error << std::endl;
	}
}

void				Bureaucrat::decrementGrade()
{
	try
	{
		if (this->_grade <= 1 || this->_grade >= 150)
			throw std::string("Bureaucrat::GradeTooLowException");
		else
			this->_grade++;
	} catch (std::string const &error)
	{
		std::cerr << error << std::endl;
	}
}

void				Bureaucrat::signForm(Form &form) const
{
	if (this->getGrade() < 1 || this->getGrade() > 150)
	{
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because its grade is invalid" << std::endl;
		return ;
	}
	else if (form.getGradeSign() < this->getGrade())
	{
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because its grade is too low" << std::endl;
		return ;
	}
	if (!form.isSigned())
	{
		form.beSigned(*this);
		std::cout << this->getName() << " signed " << form.getName();
	}
	else
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because the form is already signed";
	std::cout << std::endl;
}

std::ostream &operator << (std::ostream &flux, const Bureaucrat &object)
{
	flux << object.getName() << ", bureaucrat grade " << object.getGrade();
	return flux;
}
