#include "PmergeMe.hpp"
#include <asm-generic/errno.h>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string &args): _size(0)
{
	std::stringstream	sargs(args);
	std::string			token;

	while (sargs >> token)
	{
		this->_vector.push_back(ft_stoi(token));
		this->_list.push_back(ft_stoi(token));
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

PmergeMe::~PmergeMe() {}

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

vector<vector<int> >	PmergeMe::createPairs()
{
	std::vector<std::vector<int> >	splitArray;
	std::vector<int>				pair;
	int								straggler = this->_size % 2;

	for (size_t i = 0; i < this->_size - straggler; i += 2)
	{
		pair.push_back(this->_vector[i]);
		pair.push_back(this->_vector[i + 1]);
		splitArray.push_back(pair);
		pair.clear();
	}
	if (straggler)
	{
		pair.push_back(this->_vector[this->_size - 1]);
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

void	insertionSortPairs(vector<vector<int> > &pairs, size_t i)
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

static const unsigned int jacobstahlNumbers[] =
{
0u, 1u, 1u, 3u, 5u, 11u, 21u, 43u, 85u,
171u, 341u, 683u, 1365u, 2731u, 5461u, 10923u,
21845u, 43691u, 87381u, 174763u, 349525u
};

vector<int>				getJacobNumber(vector<int> &pend)
{
	vector<int>	end_sequence;
	int			jacobIndex = 3;
	(void)pend;

	cout << "pend size = " <<pend.size() << endl;
	while (jacobstahlNumbers[jacobIndex] < pend.size() - 1)
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
	s.insert(s.begin(), pend[0]); // OK
	// erase ou pas ?
	//pend.erase(pend.begin());

///////////////////////////////////////////////
	cout << "PEND : " << endl;
	for (size_t i = 0; i < pend.size(); ++i)
		cout << pend[i] << " ";
	cout << endl << endl;
	cout << "S : " << endl;
	for (size_t i = 0; i < s.size(); ++i)
		cout << s[i] << " ";
	cout << endl << endl;
///////////////////////////////////////////////

	size_t			iterator = 0;
	size_t			jacobIndex = 3;
	vector<int>		indexSequence;
	std::string		last = "default";
	int				item;
	vector<int>		jacobSequence = getJacobNumber(pend);

	cout << "JACOBSEQUENCE : ";
	for (size_t i = 0; i < jacobSequence.size(); ++i)
		cout << jacobSequence[i] << " ";
	cout << endl << endl;
	indexSequence.push_back(1); // first element of pend;
	while (iterator <= pend.size())
	{
		cout << "iterator : " << iterator << endl;
		if (jacobSequence.size() && last != "jacob")
		{
			cout << "===== jacob =====" << endl;
			indexSequence.push_back(jacobSequence[0]);
			cout << "INDEXSEQUENCE ";
			for (size_t i = 0; i < indexSequence.size(); ++i)
				cout << indexSequence[i] << " ";
			cout << endl;
			item = pend[jacobSequence[0] - 1];
			jacobSequence.erase(jacobSequence.begin());
			cout << "item : " << item << endl;
			last = "jacob";
		}
		else
		{
			cout << "===== not-jacob =====" << endl;
			if ( std::find(indexSequence.begin(), indexSequence.end(), iterator) != indexSequence.end())
			{
				++iterator;
				cout << "found iterator in indexsequence -> " << iterator << endl;
			}
			item = pend[iterator - 1];
			indexSequence.push_back(iterator);
			cout << "INDEXSEQUENCE ";
			for (size_t i = 0; i < indexSequence.size(); ++i)
				cout << indexSequence[i] << " ";
			cout << endl;
			cout << "item : " << item << endl;
			last = "not-jacob";
		}
		vector<int>::iterator it = std::lower_bound(s.begin(), s.end(), item);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, item);
		cout << "SEQ : ";
		for (size_t i = 0; i < s.size(); ++i)
			cout << s[i] << " ";
		cout << endl << endl;
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

void	PmergeMe::mergeInsertionSort()
{
	int						straggler = this->_size % 2 ? this->_vector[this->_size - 1] : -1;
	vector<vector<int> >	splitArray = createPairs();
	if (this->_size % 2)
		splitArray.pop_back();
	sortPairs(splitArray);
	insertionSortPairs(splitArray, splitArray.size());
/////////////////
	cout << "INSERTED PAIRS : " << endl;
	for (size_t i = 0; i < splitArray.size(); ++i)
	{
		cout << splitArray[i][0] << " ";
		if (splitArray[i].size() > 1)
			cout << splitArray[i][1] << " ";
		cout << endl;
	}
	if (this->_size % 2)
		cout << straggler << endl;
	cout << endl;
/////////////////
	vector<int> sorted = createSortedVector(splitArray, straggler); //PAS OK
	cout << "after : ";
	for (size_t i = 0; i < this->_size; ++i)
		cout << sorted[i] << " ";
	cout << endl;
}
