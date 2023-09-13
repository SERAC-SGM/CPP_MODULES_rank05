#ifndef ARRAY_H
# define ARRAY_H

template<typename T>
class Array
{
public:

	Array()
	{
		this->_array = new T[0];
	}

	Array(unsigned int n)
	{
		this->array = new T[n];
	}

	Array(const Array &toCopy)
	{
		*this = toCopy;
	}

	~Array()
	{
		delete this->_array;
	}

	unsigned int	size() const;

	Array	&operator=(const Array &rhs);

protected:

	T *_array;

};
#endif
