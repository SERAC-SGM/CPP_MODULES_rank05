#include "BitcoinExchange.hpp"
#include <climits>

BitcoinExchange::BitcoinExchange(const std::string &fileName): _fileName(fileName)
{
	fillDatabase();
	getFile(fileName);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &toCopy)
{
	*this = toCopy;
}

BitcoinExchange::~BitcoinExchange()
{
	this->_infile.close();
	this->_dataBase.close();
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this == &rhs)
		return *this;
	fillDatabase();
	getFile(rhs._fileName);
	return *this;
}

bool		BitcoinExchange::checkDate(const std::string &date) const
{

	std::istringstream dateSS(date);

	if (date.length() != 10)
		return false;
	int year, month, day;
	char dash1, dash2;
	if (!(dateSS >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (!(dateSS.eof() && dash1 == '-' && dash2 == '-'))
		return false;
	if (!(year >= 0 && month > 0 && month < 13 && day > 0))
		return false;
	int daysInMonths;
	if (month == 2) //années bissextiles
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			daysInMonths = 29;
		else
			daysInMonths = 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		daysInMonths = 30;
	else
		daysInMonths = 31;
	if (day > daysInMonths)
		return false;
	return true;
}

std::string	BitcoinExchange::getDate(std::string line) const
{
	if (line.empty())
		throw std::invalid_argument("BitcoinExchange::InvalidDate");

	size_t	len = line.size();

	if (line[len - 1] == ' ' || line[len - 1] == '\t')
		line.erase(line.size() - 1, 1);
	return line;
}

float		BitcoinExchange::ft_stof(const std::string &str) const
{
	float				number;
	std::stringstream	strStream(str);

	if (strStream >> number)
		return number;
	throw std::invalid_argument("BitcoinExchange::InvalidValue");
	return 0.0f;
}

float		BitcoinExchange::getValue(std::string line, bool db) const
{
	if (line.empty())
		throw std::invalid_argument("BitcoinExchange::EmptyValue");

	size_t	len = line.size();
	float	value;

	if (line[0] == ' ' || line[0] == '\t')
		line.erase(0, 1);
	if (line[len - 1] == '\n')
		line.erase(line.size() - 1, 1);
	value = ft_stof(line);
	//if (value < 0.0)
		//throw std::out_of_range("BitcoinExchange::NegativeValue");
	if (db && value > static_cast<float>(INT_MAX))
		throw std::out_of_range("BitcoinExchange::TooLargeValueInDataBase");
	return value;
}

void		BitcoinExchange::fillDatabase()
{
	std::string		line;
	std::ifstream	tmp(DB_NAME);

	if (!tmp)
		throw std::ios_base::failure("BitcoinExchange::InvalidDatabase");
	tmp.close();
	this->_dataBase.open(DB_NAME);
	std::getline(this->_dataBase, line);
	while(std::getline(this->_dataBase, line))
	{
		size_t separatorPos = line.find_first_of(SEPARATORS);
		if (separatorPos == std::string::npos)
			throw std::invalid_argument("BitcoinExchange::BadInputInDatabase");
		std::string date = getDate(line.substr(0, separatorPos));
		float exchangeRate = getValue(line.substr(separatorPos + 1), true);
		this->_dataBaseMap.insert(std::pair<std::string, float>(date, exchangeRate));
	}
}

void		BitcoinExchange::getFile(const std::string &file)
{
	std::ifstream	tmp(file.c_str());
	if (!tmp)
		throw std::ios_base::failure("BitcoinExchange::InvalidFile");
	tmp.close();
	this->_infile.open(file.c_str());
}

std::string	BitcoinExchange::getClosestDate(const std::string &date) const
{
	std::string newDate = "";
	for (std::map<std::string, float>::const_iterator it = this->_dataBaseMap.begin(); it != this->_dataBaseMap.end(); ++it)
	{
		if (it->first == date)
			return date;
		else if (it->first <= date && (newDate.empty() || it->first > newDate))
			newDate = it->first;
	}
	if (newDate.empty())
		throw std::invalid_argument("BitcoinExchange::DateTooLow");
	return newDate;
}

void		BitcoinExchange::convert()
{
	std::string	line;

	std::getline(this->_infile, line);
	while (std::getline(this->_infile, line))
	{
		size_t separatorPos = line.find_first_of("|");
		if (separatorPos == std::string::npos)
			throw std::invalid_argument("BitcoinExchange::BadInputInFile");
		std::string date = getDate(line.substr(0, separatorPos));
		if (!checkDate(date))
		{
			std::cout << "Error : bad input => " << date << std::endl;
			return ;
		}
		float value = getValue(line.substr(separatorPos + 1), false);
		if (value < 0.0)
			std::cout << "Error : not a positive number => " << value << std::endl;
		else if (value > 1000)
			std::cout << "Error : too large number => " << value << std::endl;
		else
		{
			std:: cout << date;
			date = getClosestDate(date);
			std::cout << " => " << value << " = " << this->_dataBaseMap[date] * value << std::endl;
		}
	}
	return ;
}

