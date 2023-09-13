#ifndef AFORM_H
# define AFORM_H

# include "Bureaucrat.hpp"
#include <string>

class Bureaucrat;

class AForm
{
public:

	AForm(const std::string name, unsigned int gradeSign, unsigned int gradeExecute);
	AForm(const AForm &toCopy);
	virtual ~AForm();

	AForm	&operator=(const AForm &rhs);

	const std::string	&getName() const;
	bool				isSigned() const;
	unsigned int		getGradeSign() const;
	unsigned int		getGradeExecute() const;
	void				beSigned(const Bureaucrat &bureaucrat);
	virtual void		execute(Bureaucrat const &executor) const = 0;

private:

	const std::string	_name;
	bool				_signed;
	const unsigned int	_requiredGradeSign;
	const unsigned int	_requiredGradeExecute;

};

std::ostream &operator << (std::ostream &flux, const AForm &object);

#endif
