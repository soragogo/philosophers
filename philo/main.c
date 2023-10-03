/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:34:27 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 19:18:20 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_pthreads(t_philo *philos, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_philo	*philos;
	int		args[5];
	t_fork	*forks;
	t_end	end;

	philos = NULL;
	ft_bzero(args, sizeof(args));
	if (error_handling(ac, av, &args) != 0)
	{
		printf("Error\n");
		return (1);
	}
	forks = create_forks(args[0]);
	if (!forks)
		return (1);
	pthread_mutex_init(&(end.lock), NULL);
	end.death = 0;
	end.eatenup = 0;
	philos = create_threads(philos, args, forks, &end);
	join_pthreads(philos, args[0]);
	free(forks);
	free(philos);
	return (0);
}
