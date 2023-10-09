#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"
#include <bits/types/clock_t.h>
#include <deque>
#include <iomanip>
#include <cstring>

const unsigned int jacobstahlNumbers[] =
{
	0u, 1u, 1u, 3u, 5u, 11u, 21u, 43u, 85u,
	171u, 341u, 683u, 1365u, 2731u, 5461u, 10923u,
	21845u, 43691u, 87381u, 174763u, 349525u
};

PmergeMe::PmergeMe() {}

bool PmergeMe::validateInput(std::string s)
{
	char *ptr = NULL;
	double value = std::strtod(s.c_str(), &ptr);
	if (value == 0.0 && !std::isdigit(s[0])) return false;
	if (*ptr && std::strcmp(ptr, "f")) return false;
	if (value < 0) return false;
	return (value == static_cast<int>(value));	
}

PmergeMe::PmergeMe(int argc, char **argv): _size(0)
{
	int i = 1;
	while (i < argc)
	{
		std::string stringTmp(argv[i]);
		std::istringstream ss(stringTmp);
		std::string stringBuffer;
		while (std::getline(ss, stringBuffer, ' '))
		{
			if (!stringBuffer.empty() && validateInput(stringBuffer) == false)
				throw std::invalid_argument("PmergeMe::InvalidType");
			if (stringBuffer.empty()) continue;
			this->_vector.push_back(static_cast<int>(std::strtod(stringBuffer.c_str(), NULL)));
		}
		++i;
	}
	this->_size = this->_vector.size();
	this->_deque.assign(this->_vector.begin(), this->_vector.end());

	cout << "Before:\t";
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

	while (jacobstahlNumbers[jacobIndex] < 21)//pend.size() - 1)
	{
		end_sequence.push_back(jacobstahlNumbers[jacobIndex]);
		++jacobIndex;
	}

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
}

void	PmergeMe::sort()
{
	if (this->_size == 1)
	{
		clock_t	start = clock();
		cout << "After:\t" << this->_vector[0] << endl;
		clock_t	end = clock();
		cout << "Time to process a range of " << std::setw(4) << this->_vector.size() << " element with std::vector : " << std::setw(10) << (end - start) / (double)CLOCKS_PER_SEC << " seconds" << endl;
		cout << "Time to process a range of " << std::setw(4) << this->_deque.size() << " element with std::deque : " << std::setw(10) << (end - start) / (double)CLOCKS_PER_SEC << " seconds" << endl;
		return ;
	}
	clock_t start = clock();
	vector<int> sorted = mergeInsertionSortVector();
	clock_t	end = clock();
	clock_t	start2 = clock();
	mergeInsertionSortDeque();
	clock_t	end2 = clock();
	cout << "After:\t";
	for (size_t i = 0; i < this->_size; ++i)
		cout << sorted[i] << " ";
	cout << endl;
	cout << "Time to process a range of " << std::setw(4) << this->_vector.size() << " elements with std::vector : " << std::setw(10) << (end - start) / (double)CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Time to process a range of " << std::setw(4) << this->_deque.size() << " elements with std::deque : " << std::setw(10) << (end2 - start2) / (double)CLOCKS_PER_SEC << " seconds" << endl;
}

#endif
