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

	bool							isInt(const std::string &);
	int								ft_stoi(const std::string &);
	std::vector<std::vector<int> >	createPairs();
	void							sortPairs(std::vector<std::vector<int> > &);
	void							sortByLargerValue(std::vector<std::vector<int> > &);
	std::vector<int>				createSortedVector(std::vector<std::vector<int> > &, int);
	void							mergeInsertionSort();

protected:

	std::size_t					_size;
	std::vector<int>			_vector;
	std::list<int>				_list;

};
#endif
