#include "Span.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <climits>
#include <list>
#include <iostream>

Span::Span(unsigned int N): _n(N) {}

Span::Span(const Span &toCopy)
{
	*this = toCopy;
}

Span::~Span() {}

Span	&Span::operator=(const Span &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

void	Span::addNumber(int n)
{
	if (this->_n == 0)
		throw std::out_of_range("Span::addNumber: list is full");
	if (this->_list.size() + 1 > this->_n)
		throw std::out_of_range("Span::addNumber: list is full");
	this->_list.push_back(n);
}

void Span::addNumber( std::list<int>::const_iterator itBegin, std::list<int>::const_iterator itEnd )
{
	if ( _list.size() > _n )
		throw std::out_of_range("Span::addNumber: list is full");
	_list.insert( _list.end(), itBegin, itEnd );
}

unsigned int	Span::shortestSpan()
{
	if (this->_list.size() < 2)
		throw std::runtime_error("Span::shortestSpan: list needs at least 2 elements");
	
	this->_list.sort();
	std::list<int>::iterator	it = this->_list.begin();
	int							previous = *it;
	unsigned int				span = UINT_MAX;

	++it;
	while (it != this->_list.end())
	{
		unsigned int diff = *it - previous;
		span = std::min(span, diff);
		previous = *it;
		++it;
	}
	return span;
}

unsigned int	Span::longestSpan()
{
	if (this->_list.size() < 2)
		throw std::runtime_error("Span::longestSpan: list needs at least 2 elements");
	
	return *std::max_element(this->_list.begin(), this->_list.end()) - *std::min_element(this->_list.begin(), this->_list.end());

}


