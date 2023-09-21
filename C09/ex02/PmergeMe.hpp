#ifndef PMERGEME_H
# define PMERGEME_H

# include <climits>
# include <cstddef>
# include <cctype>
# include <string>
# include <sstream>
# include <vector>
# include <list>
# include <iostream>

class PmergeMe
{
public:

	PmergeMe();
	PmergeMe(const std::string &);
	PmergeMe(const PmergeMe &toCopy);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &rhs);

	bool		isInt(const std::string &);
	int			ft_stoi(const std::string &);
	void		sort();

protected:

	std::size_t					_size;
	std::vector<int>			_vector;
	std::list<int>				_list;

};
#endif
