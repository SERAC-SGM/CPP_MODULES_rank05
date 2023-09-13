#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# include <string>
# include <iostream>

class Bureaucrat
{
public:

	Bureaucrat(const std::string &name, unsigned int grade);
	Bureaucrat(const Bureaucrat &toCopy);
	~Bureaucrat();

	Bureaucrat	&operator=(const Bureaucrat &rhs);

	const std::string	&getName() const;
	unsigned int		getGrade() const;
	void				incrementGrade();
	void				decrementGrade();

protected:

	const std::string	_name;
	unsigned int		_grade;

};

std::ostream &operator << (std::ostream &flux, const Bureaucrat &object);

#endif
