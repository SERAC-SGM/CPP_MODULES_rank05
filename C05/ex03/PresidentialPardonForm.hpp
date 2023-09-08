#ifndef PRESIDENTIALPARDONFORM_H
# define PRESIDENTIALPARDONFORM_H

#include "AForm.hpp"

class PresidentialPardonForm: public AForm
{
public:

	PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &toCopy);
	virtual ~PresidentialPardonForm();

	PresidentialPardonForm	&operator=(const PresidentialPardonForm &rhs);

	virtual void	execute(Bureaucrat const &executor) const;

protected:

	const std::string	_target;

};
#endif
