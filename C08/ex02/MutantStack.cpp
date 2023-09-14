#include "MutantStack.hpp"

MutantStack::MutantStack()
{}

MutantStack::MutantStack(const MutantStack &toCopy)
{
	*this = toCopy;
}

MutantStack::~MutantStack()
{}

MutantStack	&MutantStack::operator=(const MutantStack &rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}