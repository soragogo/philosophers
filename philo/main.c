/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:34:27 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 18:36:06 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	*philos;
	int		args[5];
	t_forks	*forks;
	t_end	end;
	int		i;

	i = 0;
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
	while (i < args[0])
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(forks);
	free(philos);
	return (0);
}
