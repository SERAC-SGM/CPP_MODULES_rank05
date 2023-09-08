#include "ScalarConverter.hpp"
#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;

ScalarConverter::ScalarConverter()
{}

ScalarConverter::ScalarConverter(const ScalarConverter &toCopy)
{
	*this = toCopy;
}

ScalarConverter::~ScalarConverter()
{}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

static bool	isChar(const std::string &str)
{
	if (str.length() != 1)
		return false;
	if (str[0] < std::numeric_limits<char>::min()
	|| str[0] > std::numeric_limits<char>::max()
	|| isdigit(str[0]))
		return false;
	return true;
}

static bool	isInt(const std::string &str)
{
	size_t	i = 0;
	if (str[0] == '-')
		i++;
	while (i < str.length())
	{
		if (!isdigit(str[i++]))
			return false;
	}
	return true;
}

static bool	isFloat(const std::string &str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf")
		return true;
	if (str[str.length() - 1] != 'f')
		return false;
	if (str[0] == '-')
	{
		return (isFloat(str.substr(1)));
	}
	int isDot = 0;
	for (size_t i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == '.')
		{
			isDot++;
			if (isDot > 1)
				return false;
		}
		else if (!isdigit(str[i]))
			return false;
	}
	return true;
}

static bool	isDouble(const std::string &str)
{
	if (str == "-inf" || str == "+inf" || str == "nan")
		return true;
	int isDot = 0;
	if (str[0] == '-')
	{
		return (isDouble(str.substr(1)));
	}
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			isDot++;
			if (isDot > 1)
				return false;
		}
		else if (!isdigit(str[i]))
			return false;
	}
	return true;
}

static bool isPseudoLiteral(const std::string& str)
{
	return (str == "-inff" || str == "+inff" || str == "nanf"
			|| str == "-inf" || str == "+inf" || str == "nan");
}

enum literalType
{
	error,
	_char,
	_int,
	_float,
	_double
};

static literalType getType(const std::string &str)
{
	if (isChar(str))
		return _char;
	if (isInt(str))
		return _int;
	if (isFloat(str))
		return _float;
	if (isDouble(str))
		return _double;
	return error;
}

static void	printChar(char c)
{
	cout << "char: '" << c << "'" << endl;
	cout << "int: " << static_cast<int>(c) << endl;
	cout << "float: " << static_cast<float>(c) << ".0f" << endl;
	cout << "double: " << static_cast<double>(c) << ".0" << endl;
}

static void	printInt(int n)
{
	if (n >= 32 && n <= 126)
		cout << "char: '" << static_cast<char>(n) << "'" << endl;
	else
		cout << "char: Non displayable" << endl;
	cout << "int: " << n << endl;
	cout << "float: " << static_cast<float>(n) << ".0f" << endl;
	cout << "double: " << static_cast<double>(n) << ".0" << endl;
}

static void	printFloat(float n)
{
	if (n >= 32 && n <= 126)
		cout << "char: '" << static_cast<char>(n) << "'" << endl;
	else
		cout << "char: Non displayable" << endl;
	cout << "int: " << static_cast<int>(n) << endl;
	cout << "float: " << n << "f" << endl;
	cout << "double: " << static_cast<double>(n) << endl;
}

static void	printDouble(double n)
{
	if (n >= 32 && n <= 126)
		cout << "char: '" << static_cast<char>(n) << "'" << endl;
	else
		cout << "char: Non displayable" << endl;
	cout << "int: " << static_cast<int>(n) << endl;
	cout << "float: " << static_cast<float>(n) << "f" << endl;
	cout << "double: " << n << endl;
}

static void printPseudoLiteral(literalType dest, const std::string &pseudoLiteral)
{
	cout << "char: impossible" << endl;
	cout << "int: impossible" << endl;
	if (dest == _float)
	{
		cout << ": " << pseudoLiteral << endl;
		cout << ": " << pseudoLiteral.substr(0, pseudoLiteral.length() - 1) << endl;
	}
	else if (dest == _double)
	{
		cout << ": " << pseudoLiteral + "f" << endl;
		cout << ": " << pseudoLiteral << endl;
	}
}

static int ft_stoi(const std::string &str)
{
	int					number;
	std::stringstream	strStream(str);

	try {
		if (strStream >> number)
			return number;
		throw std::string("the string does not contain a valid integer");
	} catch (std::string const &error) {
		std::cerr << error << endl;
	}
	return (0);
}

static float	ft_stof(const std::string &str)
{
	float				number;
	std::stringstream	strStream(str);

	try {
		if (strStream >> number)
			return number;
		throw std::string("the string does not contain a valid float");
	} catch (std::string const &error) {
		std::cerr << error << endl;
	}
	return (0.0f);
}

static double	ft_stod(const std::string &str)
{
	double				number;
	std::stringstream	strStream(str);

	try {
		if (strStream >> number)
			return number;
		throw std::string("the string does not contain a valid double");
	} catch (std::string const &error) {
		std::cerr << error << endl;
	}
	return (0.0);
}

void	ScalarConverter::convert(const std::string &input)
{
	switch (getType(input))
	{
		case _char:
			printChar(input[0]);
			break;
		case _int:
			printInt(ft_stoi(input));
			break;
		case _float:
			if(!isPseudoLiteral(input))
				printFloat(ft_stof(input));
			else
				printPseudoLiteral(_float, input);
			break;
		case _double:
			if (!isPseudoLiteral(input))
				printDouble(ft_stod(input));
			else
				printPseudoLiteral(_double, input);
			break;
		default:
			cout << "Unknown type" << endl;
	}
}
