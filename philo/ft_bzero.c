#include "philo.h"
void *ft_bzero(void *b, int n)
{
	char *p;
	int i;

	p = b;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
	return (b);
}
