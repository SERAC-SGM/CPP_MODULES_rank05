#ifndef RPN_H
# define RPN_H

# include <stack>
# include <string>
# include <sstream>

class RPN
{
private:

	RPN();
	RPN(const RPN &toCopy);
	~RPN();

	RPN	&operator=(const RPN &rhs);

	static int	compute(std::string, int, int);
	static int	ft_stoi(std::string);

public:

	static int	evaluateRPN(std::string);

};
#endif
