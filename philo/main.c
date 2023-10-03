#include "philo.h"

int main(int ac, char *av[])
{
	t_philo *philos = NULL;
	int args[5];
	t_fork *forks;
	t_end end;
	int i = 0;

	ft_bzero(args, sizeof(args));
	if (error_handling(ac, av, &args) != 0)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	forks = create_forks(args[0]);
	if (!forks)
		return (1);
	pthread_mutex_init(&(end.lock), NULL);
	end.death = 0;
	end.eatenup = 0;
	philos = create_threads(philos, args, forks, &end);
	while (i < args[0])
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(forks);
	free(philos);

	return 0;
}
