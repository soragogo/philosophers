/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:34:27 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 21:44:07 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_and_free(t_philo *philos, t_fork *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(forks);
	free(philos);
}

void	init_end_flag(t_end *end)
{
	pthread_mutex_init(&(end->lock), NULL);
	end->death = 0;
	end->eatenup = 0;
}

int	main(int ac, char *av[])
{
	t_philo	*philos;
	int		args[5];
	t_fork	*forks;
	t_end	end;

	philos = NULL;
	if (av[5] && ft_strncmp(av[5], "0", 2) == 0)
		return (0);
	ft_bzero(args, sizeof(args));
	if (error_handling(ac, av, &args) != 0)
	{
		printf("Error\n");
		return (1);
	}
	init_end_flag(&end);
	forks = create_forks(args[0]);
	if (!forks)
		return (1);
	philos = create_threads(philos, args, forks, &end);
	if (!philos)
		return (1);
	join_and_free(philos, forks, args[0]);
	return (0);
}
