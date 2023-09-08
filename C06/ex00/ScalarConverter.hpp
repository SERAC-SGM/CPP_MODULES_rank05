#ifndef SCALARCONVERTER_H
# define SCALARCONVERTER_H

#include <string>
class ScalarConverter
{
public:

	ScalarConverter();
	ScalarConverter(const ScalarConverter &toCopy);
	~ScalarConverter();

	ScalarConverter	&operator=(const ScalarConverter &rhs);

	static void	convert(const std::string &input);

};
#endif
