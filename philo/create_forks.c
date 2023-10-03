#include "philo.h"

t_fork *create_forks(int num_of_philos)
{
	t_fork *forks;
	int i;

	i = 0;
	forks = calloc(num_of_philos, sizeof(t_fork));

	if (!forks)
		return (NULL);
	while (i < num_of_philos)
	{
		pthread_mutex_init(&(forks[i].lock), NULL);
		forks[i].is_available = true;
		// forks[i].num = i;
		forks[i].history = 1;
		i++;
	}
	return forks;
}
