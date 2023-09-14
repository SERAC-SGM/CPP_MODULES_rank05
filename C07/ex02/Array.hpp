#ifndef ARRAY_H
# define ARRAY_H

#include <stdexcept>
#include <iostream>

template<typename T>
class Array
{
public:

	Array(): _array(0), _size(0) {}

	Array(unsigned int n): _size(n)
	{
		this->_array = new T[n];
		for (unsigned i = 0; i < n; i++)
			this->_array[i] = T();
	}

	Array(const Array &toCopy): _array(new T[toCopy._size]), _size(toCopy._size) 
	{
		*this = toCopy;
	}

	~Array()
	{
		delete [] this->_array;
	}

	unsigned int	size() const
	{
		return this->_size;
	}

	Array	&operator=(const Array &rhs)
	{
		if (this == &rhs)
			return *this;
		delete [] this->_array;
		this->_size = rhs._size;
		this->_array = new T[this->_size];
		for (unsigned int i = 0; i < this->_size; i++)
			this->_array[i] = rhs._array[i];
		return *this;
	}

	T	&operator[](unsigned int index)
	{
		if (index >= this->_size)
			throw std::out_of_range("Index out of range");
		return this->_array[index];
	}

protected:

	T				*_array;
	unsigned int	_size;

};
#endif
