#include "Array.hpp"

Array::Array()
{}

Array::Array(const Array &toCopy)
{
	*this = toCopy;
}

Array::~Array()
{}

Array	&Array::operator=(const Array &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}