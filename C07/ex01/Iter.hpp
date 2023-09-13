#ifndef ITER_H
# define ITER_H

# include <iostream>

template<typename T>
void	print(T &elem)
{
	std::cout << elem << std::endl;
}

template<typename T, typename S>
void	iter(T *array, int length, void(*fct)(S &))
{
	for (int i = 0; i < length; i++)
		fct(array[i]);
}

#endif
