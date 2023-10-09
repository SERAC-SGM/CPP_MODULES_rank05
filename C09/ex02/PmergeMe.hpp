#ifndef PMERGEME_H
# define PMERGEME_H

# include <climits>
# include <cstddef>
# include <cctype>
# include <deque>
# include <string>
# include <sstream>
# include <vector>
# include <iostream>
# include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::deque;

class PmergeMe
{
public:

	PmergeMe(int argc, char **argv);
	PmergeMe(const PmergeMe &toCopy);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &rhs);

	void		sort();

protected:

	PmergeMe();

	bool 					validateInput(std::string s);
	bool					isInt(const std::string &);
	int						ft_stoi(const std::string &);
	vector<vector<int> >	createPairs(vector<int> &container);
	deque<deque<int> >		createPairsDeque(deque<int> &container);
	void					sortPairs(vector<vector<int> > &);
	void					sortPairsDeque(deque<deque<int> > &);
	void					insertionSortPairs(vector<vector<int> > &pairs, size_t i);
	void					insertionSortPairsDeque(deque<deque<int> > &pairs, size_t i);
	vector<int>				createSortedVector(vector<vector<int> > &, int);
	deque<int>				createSortedDeque(deque<deque<int> > &, int);
	vector<int>				mergeInsertionSortVector();
	void					mergeInsertionSortDeque();

	template<typename T>
	T				getJacobNumber(T &pend);

	std::size_t					_size;
	std::vector<int>			_vector;
	std::vector<int>			_sorted;
	std::deque<int>				_deque;

};

#endif
