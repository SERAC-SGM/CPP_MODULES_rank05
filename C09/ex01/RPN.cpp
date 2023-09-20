#include "RPN.hpp"
#include <cctype>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

RPN::RPN() {}

RPN::RPN(const RPN &toCopy)
{
	*this = toCopy;
}

RPN::~RPN() {}

RPN	&RPN::operator=(const RPN &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

int	RPN::compute(std::string token, int lhs, int rhs)
{
	if (token == "+")
		return lhs + rhs;
	else if (token == "-")
		return lhs - rhs;
	else if (token == "*")
		return lhs * rhs;
	else if (token == "/")
	{
		if (rhs == 0)
			throw std::runtime_error("RPN::DivisionByZero");
		return lhs / rhs;
	}
	throw std::invalid_argument("RPN::InvalidOperator");
	return 0;
}

int	RPN::ft_stoi(std::string str)
{
	int		number = 0;
	bool	negative = false;
	size_t	i = 0;

	if (str[0] == '-')
	{
		negative = true;
		++i;
	}
	while (i < str.size())
	{
		if (std::isdigit(str[i]))
			number = number * 10 + (str[i] - '0');
		else
			throw std::invalid_argument("RPN::InvalidOperand");
		i++;
	}
	if (negative)
		return -number;
	return number;
}

int	RPN::evaluateRPN(std::string str)
{
	std::stringstream	sstr(str);
	std::string			token;
	std::stack<int>		operands;

	while (sstr >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (operands.size() < 2)
				throw std::invalid_argument("RPN::NotEnoughOperands");
			int rightOperand = operands.top();
			operands.pop();
			int leftOperand = operands.top();
			operands.pop();
			int result = compute(token, leftOperand, rightOperand);
			operands.push(result);
		}
		else
		{
			int operand = ft_stoi(token);
			operands.push(operand);
		}
	}
	if (operands.empty())
		throw std::invalid_argument("RPN::NotEnoughOperands");
	if (operands.size() != 1)
		throw std::invalid_argument("RPN::NotEnoughOperators");
	return operands.top();
}
