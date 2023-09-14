#ifndef SPAN_H
# define SPAN_H

# include <list>

class Span
{
public:

	Span(unsigned int N);
	Span(const Span &toCopy);
	~Span();

	Span	&operator=(const Span &rhs);

	void			addNumber(int n);
	void			addNumber( std::list<int>::const_iterator itBegin, std::list<int>::const_iterator itEnd );
	unsigned int	shortestSpan();
	unsigned int	longestSpan();

protected:

	std::list<int>	_list;
	unsigned int	_n;

};
#endif
