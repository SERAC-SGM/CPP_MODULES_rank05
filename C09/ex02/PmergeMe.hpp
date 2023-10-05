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

template<typename T, typename U>
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
	//template<typename U>
	T<U> createPairs(T<U> &container)
	{
		T<T<int> >	splitArray;
		T<int>		pair;
		int			straggler = this->_size % 2;

		for (size_t i = 0; i < this->_size - straggler; i += 2)
		{
			pair.push_back(container[i]);
			pair.push_back(container[i + 1]);
			splitArray.push_back(pair);
			pair.clear();
		}
		if (straggler)
		{
			pair.push_back(container[this->_size - 1]);
			splitArray.push_back(pair);
		}
		return splitArray;
	}
	void	sortPairs(T<T<int> > &);
	void	sortByLargerValue(T<T<int> > &);
	T<int>	createSortedVector(T<T<int> > &, int);
	void	mergeInsertionSort(T &);

protected:

	std::size_t					_size;
	std::vector<int>			_vector;
	std::list<int>				_list;

};

#include "PmergeMe.tpp"

#endif
