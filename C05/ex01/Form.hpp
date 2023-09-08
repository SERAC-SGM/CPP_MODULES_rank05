#ifndef FORM_H
# define FORM_H

# include "Bureaucrat.hpp"
#include <string>

class Form
{
public:

	Form(const std::string name, unsigned int gradeSign, unsigned int gradeExecute);
	Form(const Form &toCopy);
	virtual ~Form();

	Form	&operator=(const Form &rhs);

	const std::string	&getName() const;
	bool				isSigned() const;
	unsigned int		getGradeSign() const;
	unsigned int		getGradeExecute() const;
	void				beSigned(const Bureaucrat &bureaucrat);
	void				signAForm(const Bureaucrat &bureaucrat);

private:

	const std::string	_name;
	bool				_signed;
	const unsigned int	_requiredGradeSign;
	const unsigned int	_requiredGradeExecute;

};

std::ostream &operator << (std::ostream &flux, const Form &object);

#endif
