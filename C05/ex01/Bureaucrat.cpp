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
{
	std::cout << "destroying " << this->_name << std::endl;
}

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

std::ostream &operator << (std::ostream &flux, const Bureaucrat &object)
{
	flux << object.getName() << ", bureaucrat grade " << object.getGrade();
	return flux;
}
