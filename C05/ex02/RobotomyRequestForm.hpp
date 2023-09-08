#ifndef ROBOTOMYREQUESTFORM_H
# define ROBOTOMYREQUESTFORM_H

#include <ctime>
#include "AForm.hpp"

class RobotomyRequestForm: public AForm
{
public:

	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &toCopy);
	virtual ~RobotomyRequestForm();

	RobotomyRequestForm	&operator=(const RobotomyRequestForm &rhs);

	virtual void	execute(Bureaucrat const &executor) const;

protected:

	const std::string	_target;

};
#endif
