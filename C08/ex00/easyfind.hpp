#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>
#include <iostream>

template<typename T>
void	easyfind(T &param, int i)
{
	if (std::find(param.begin(), param.end(), i) != param.end())
		std::cout << "Found" << std::endl;
	else
		std::cout << "Not found" << std::endl;
}

#endif
