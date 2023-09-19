#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <map>
# include <string>
# include <iostream>
# include <ostream>
# include <fstream>
# include <sstream>
# include <climits>
# include <exception>

# define DB_NAME "data.csv"
# define SEPARATORS ",|"

class BitcoinExchange
{
public:

	BitcoinExchange(const std::string &);
	BitcoinExchange(const BitcoinExchange &toCopy);
	~BitcoinExchange();

	bool		checkDate(const std::string &) const;
	std::string	getDate(std::string line) const;
	float		ft_stof(const std::string &) const;
	float		getValue(std::string line, bool db) const;
	void		fillDatabase();
	void		getFile(const std::string &);
	std::string	getClosestDate(const std::string &) const;
	void		convert();

	BitcoinExchange	&operator=(const BitcoinExchange &rhs);

protected:

	std::string						_fileName;
	std::ifstream					_infile;
	std::ifstream					_dataBase;
	std::map<std::string, float>	_dataBaseMap;

};
#endif
