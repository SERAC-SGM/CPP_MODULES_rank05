#include "PmergeMe.hpp"
#include <cctype>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string &args): _size(0)
{
	std::stringstream	sargs(args);
	std::string			token;

	while (sargs >> token)
	{
		this->_vector.push_back(ft_stoi(token));
		this->_list.push_back(ft_stoi(token));
		++this->_size;
	}
	cout << "before : ";
	for (size_t i = 0; i < this->_size; ++i)
		cout << this->_vector[i] << " ";
	cout << endl;
}

PmergeMe::PmergeMe(const PmergeMe &toCopy)
{
	*this = toCopy;
}

PmergeMe::~PmergeMe() {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

int		PmergeMe::ft_stoi(const std::string &str)
{
	long int		number = 0;
	bool			negative = false;
	size_t			i = 0;

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
			throw std::invalid_argument("PmergeMe::InvalidType");
		i++;
	}
	if (number > INT_MAX)
		throw std::invalid_argument("PmergeMe::NumberTooLarge");
	if (negative)
		return -number;
	return number;
}
