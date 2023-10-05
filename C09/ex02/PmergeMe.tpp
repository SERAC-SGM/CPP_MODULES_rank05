#ifndef PMERGEME_TPP
# define PMERGEME_TPP

using std::cout;
using std::endl;

PmergeMe<T>::PmergeMe() {}

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

template<typename T>
template<typename U>
T<U>	PmergeMe<T>::createPairs(T<U> &container)
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

template<typename T>
template<typename U>
void	PmergeMe<T>::sortPairs(T<T<int> > &pairs)
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

template<typename T>
template<typename U>
void	insertionSortPairs(T<U> > &pairs, size_t i)
{
	if (i == 0)
		return ;
	insertionSortPairs(pairs, i - 1);

	T<int>	last = pairs[i - 1];
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

template<typename T>
T<int>				getJacobNumber(T<int> &pend)
{
	T<int>	end_sequence;
	int		jacobIndex = 3;
	(void)pend;

	while (jacobstahlNumbers[jacobIndex] < 21)//pend.size() - 1)
	{
		end_sequence.push_back(jacobstahlNumbers[jacobIndex]);
		++jacobIndex;
	}
	return end_sequence;
}

template<typename T>
template<typename U>
T<int>	PmergeMe::createSortedVector(T<T<int> > &sortedSplitArray, int straggler)
{
	T<int>	s;
	T<int>	pend;
	size_t	i = -1;

	while (++i < sortedSplitArray.size())
	{
		s.push_back(sortedSplitArray[i][1]);
		pend.push_back(sortedSplitArray[i][0]);
	}
	s.insert(s.begin(), pend[0]);

	size_t		iterator = 0;
	size_t		jacobIndex = 3;
	T<int>		indexSequence;
	std::string	last = "default";
	int			item;
	T<int>		jacobSequence = getJacobNumber(pend);

	indexSequence.push_back(1); // first element of pend;
	while (iterator <= pend.size())
	{
		if (jacobSequence.size() && last != "jacob")
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
			item = pend[iterator - 1];
			indexSequence.push_back(iterator);
			last = "not-jacob";
		}
		T<int>::iterator it = std::lower_bound(s.begin(), s.end(), item);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, item);
		++jacobIndex;
		++iterator;
	}

	if (this->_size % 2)
	{
		T<int>::iterator it = std::lower_bound(s.begin(), s.end(), straggler);
		int insertionPoint = std::distance(s.begin(), it);
		s.insert(s.begin() + insertionPoint, straggler);
	}
	return s;
}

template<typename T>
void	PmergeMe::mergeInsertionSort(T &container)
{
	int			straggler = this->_size % 2 ? container[this->_size - 1] : -1;
	T<T<int> >	splitArray = createPairs();

	if (this->_size % 2)
		splitArray.pop_back();
	sortPairs(splitArray);
	insertionSortPairs(splitArray, splitArray.size());
	T<int> sorted = createSortedVector(splitArray, straggler);
	cout << "after : ";
	for (size_t i = 0; i < this->_size; ++i)
		cout << sorted[i] << " ";
	cout << endl;
}

#endif
