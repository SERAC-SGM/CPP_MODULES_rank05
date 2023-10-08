#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"
#include <deque>

const unsigned int jacobstahlNumbers[] =
{
	0u, 1u, 1u, 3u, 5u, 11u, 21u, 43u, 85u,
	171u, 341u, 683u, 1365u, 2731u, 5461u, 10923u,
	21845u, 43691u, 87381u, 174763u, 349525u
};

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string &args): _size(0)
{
	std::stringstream	sargs(args);
	std::string			token;

	while (sargs >> token)
	{
		this->_vector.push_back(ft_stoi(token));
		this->_deque.push_back(ft_stoi(token));
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

PmergeMe::~PmergeMe()
{
	this->_deque.clear();
	this->_vector.clear();
	this->_sorted.clear();

}

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
		return -static_cast<int>(number);
	return static_cast<int>(number);
}

vector<vector<int> >	PmergeMe::createPairs(vector<int> &container)
{
	vector<vector<int> >	splitArray;
	vector<int>				pair;
	int						straggler = this->_size % 2;

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

deque<deque<int> >	PmergeMe::createPairsDeque(deque<int> &container)
{
	deque<deque<int> >	splitArray;
	deque<int>			pair;
	int					straggler = this->_size % 2;

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

void	PmergeMe::sortPairs(vector<vector<int> > &pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i].size() == 2 && pairs[i][0] > pairs[i][1])
		{
			int temp = pairs[i][0];
			pairs[i][0] = pairs[i][1];
			pairs[i][1] = temp;
		}
	}
}

void	PmergeMe::sortPairsDeque(deque<deque<int> > &pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i].size() == 2 && pairs[i][0] > pairs[i][1])
		{
			int temp = pairs[i][0];
			pairs[i][0] = pairs[i][1];
			pairs[i][1] = temp;
		}
	}
}

void	PmergeMe::insertionSortPairs(vector<vector<int> > &pairs, size_t i)
{
	if (i == 0)
		return ;
	insertionSortPairs(pairs, i - 1);

	vector<int>	last = pairs[i - 1];
	int	j = i - 2;
	while (j >= 0 && pairs[j][1] > last[1])
	{
		pairs[j + 1] = pairs[j];
		--j;
	}
	pairs[j + 1] = last;
	return ;
}

void	PmergeMe::insertionSortPairsDeque(deque<deque<int> > &pairs, size_t i)
{
	if (i == 0)
		return ;
	insertionSortPairsDeque(pairs, i - 1);

	deque<int>	last = pairs[i - 1];
	int	j = i - 2;
	while (j >= 0 && pairs[j][1] > last[1])
	{
		pairs[j + 1] = pairs[j];
		--j;
	}
	pairs[j + 1] = last;
	return ;
}

template<typename T>
T				PmergeMe::getJacobNumber(T &pend)
{
	T	end_sequence;
	int	jacobIndex = 3;
	(void)pend;

//	if (pend.size < )

	// cout << "pend size - 1 = " << pend.size() - 1 << endl;
	while (jacobstahlNumbers[jacobIndex] < 21)//pend.size() - 1)
	{
		end_sequence.push_back(jacobstahlNumbers[jacobIndex]);
		++jacobIndex;
	}
	// cout << "JACOB : " << endl;
	// for (size_t i = 0; i < end_sequence.size(); ++i)
	// 	cout << end_sequence[i] << " ";
	// cout << endl;
	return end_sequence;
}

vector<int>	PmergeMe::createSortedVector(vector<vector<int> > &sortedSplitArray, int straggler)
{
	vector<int>	s;
	vector<int>	pend;
	size_t		i = -1;

	while (++i < sortedSplitArray.size())
	{
		s.push_back(sortedSplitArray[i][1]);
		pend.push_back(sortedSplitArray[i][0]);
	}
	s.insert(s.begin(), pend[0]);

// ///////////////////////////////////////////////
// 	cout << "PEND : " << endl;
// 	for (size_t i = 0; i < pend.size(); ++i)
// 		cout << pend[i] << " ";
// 	cout << endl << endl;
// 	cout << "S : " << endl;
// 	for (size_t i = 0; i < s.size(); ++i)
// 		cout << s[i] << " ";
// 	cout << endl << endl;
// ///////////////////////////////////////////////

	size_t			iterator = 0;
	size_t			jacobIndex = 3;
	vector<int>		indexSequence;
	std::string		last = "default";
	int				item;
	vector<int>		jacobSequence = getJacobNumber(pend);

	indexSequence.push_back(1); // first element of pend;
	while (iterator <= pend.size())
	{
		if (jacobSequence.size() && last != "jacob" && pend.size() > 4)
		{
			indexSequence.push_back(jacobSequence[0]);
			item = pend[jacobSequence[0] - 1];
			jacobSequence.erase(jacobSequence.begin());
			last = "jacob";
		}
		else
		{
			if ( std::find(indexSequence.begin(), indexSequence.end(), iterator) != indexSequence.end())
				++iterator;
			if (iterator == 0)
				iterator = 2;
			item = pend[iterator - 1];
			indexSequence.push_back(iterator);
			last = "not-jacob";
		}
		vector<int>::iterator it = std::lower_bound(s.begin(), s.end(), item);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, item);
		++jacobIndex;
		++iterator;

		// cout << "S : " << endl;
		// for (size_t i = 0; i < s.size(); ++i)
		// 	cout << s[i] << " ";
		// cout << endl << endl;
	}

	if (this->_size % 2)
	{
		vector<int>::iterator it = std::lower_bound(s.begin(), s.end(), straggler);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, straggler);
	}
	return s;
}

deque<int>		PmergeMe::createSortedDeque(deque<deque<int> > &sortedSplitArray, int straggler)
{
	deque<int>	s;
	deque<int>	pend;
	size_t		i = -1;

	while (++i < sortedSplitArray.size())
	{
		s.push_back(sortedSplitArray[i][1]);
		pend.push_back(sortedSplitArray[i][0]);
	}
	s.insert(s.begin(), pend[0]);

	size_t			iterator = 0;
	size_t			jacobIndex = 3;
	deque<int>		indexSequence;
	std::string		last = "default";
	int				item;
	deque<int>		jacobSequence = getJacobNumber(pend);

	indexSequence.push_back(1); // first element of pend;
	while (iterator <= pend.size())
	{
		if (jacobSequence.size() && last != "jacob" && pend.size() > 4)
		{
			indexSequence.push_back(jacobSequence[0]);
			item = pend[jacobSequence[0] - 1];
			jacobSequence.erase(jacobSequence.begin());
			last = "jacob";
		}
		else
		{
			if ( std::find(indexSequence.begin(), indexSequence.end(), iterator) != indexSequence.end())
				++iterator;
			if (iterator == 0)
				iterator = 2;
			item = pend[iterator - 1];
			indexSequence.push_back(iterator);
			last = "not-jacob";
		}
		deque<int>::iterator it = std::lower_bound(s.begin(), s.end(), item);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, item);
		++jacobIndex;
		++iterator;
	}

	if (this->_size % 2)
	{
		deque<int>::iterator it = std::lower_bound(s.begin(), s.end(), straggler);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, straggler);
	}
	return s;
}

vector<int>	PmergeMe::mergeInsertionSortVector()
{
	int			straggler = this->_size % 2 ? this->_vector[this->_size - 1] : -1;
	vector<vector<int> >	splitArray = createPairs(this->_vector);

	if (this->_size % 2)
		splitArray.pop_back();
	sortPairs(splitArray);
	insertionSortPairs(splitArray, splitArray.size());
// /////////////////
// 	cout << "INSERTED PAIRS : " << endl;
// 	for (size_t i = 0; i < splitArray.size(); ++i)
// 	{
// 		cout << splitArray[i][0] << " ";
// 		if (splitArray[i].size() > 1)
// 			cout << splitArray[i][1] << " ";
// 		cout << endl;
// 	}
// 	if (this->_size % 2)
// 		cout << straggler << endl;
// 	cout << endl;
// /////////////////
	vector<int> sorted = createSortedVector(splitArray, straggler);
	return sorted;
}

void	PmergeMe::mergeInsertionSortDeque()
{
	int			straggler = this->_size % 2 ? this->_vector[this->_size - 1] : -1;
	deque<deque<int> >	splitArray = createPairsDeque(this->_deque);

	if (this->_size % 2)
		splitArray.pop_back();
	sortPairsDeque(splitArray);
	insertionSortPairsDeque(splitArray, splitArray.size());
	deque<int> sorted = createSortedDeque(splitArray, straggler);
	// cout << "deque after : ";
	// for (size_t i = 0; i < this->_size; ++i)
	// 	cout << sorted[i] << " ";
	// cout << endl;
}

void	PmergeMe::sort()
{
	//CLOCK START
	vector<int> sorted = mergeInsertionSortVector();
	//CLOCK END
	//CLOCK START
	mergeInsertionSortDeque();
	//CLOCK END
	cout << "after : ";
	for (size_t i = 0; i < this->_size; ++i)
		cout << sorted[i] << " ";
	cout << endl;
}

#endif
