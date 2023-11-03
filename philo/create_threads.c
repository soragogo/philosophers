/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:44:59 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/03 20:07:42 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philos_args(t_philo *philos,
						int *args, t_fork *forks, t_end *end)
{
	int	i;

	i = 0;
	while (i < args[0])
	{
		philos[i].name = i;
		if (args[4])
			philos[i].meals_to_eat = args[4];
		else
			philos[i].meals_to_eat = -1;
		philos[i].end_flag = end;
		philos[i].fork[LEFT] = &forks[i];
		if (i + 1 < args[0])
			philos[i].fork[RIGHT] = &forks[i + 1];
		else
			philos[i].fork[RIGHT] = &forks[0];
		philos[i].die_duration = args[1];
		philos[i].eat_duration = args[2];
		philos[i].sleep_duration = args[3];
		i++;
	}
}

pthread_mutex_t	*set_philos(t_philo *philos,
						int *args, t_fork *forks, t_end *end)
{
	int				i;
	pthread_mutex_t	*print_mutex;

	print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (NULL);
	set_philos_args(philos, args, forks, end);
	pthread_mutex_init(print_mutex, NULL);
	i = 0;
	while (i < args[0])
	{
		philos[i].print_mutex = print_mutex;
		i++;
	}
	return (print_mutex);
}

pthread_mutex_t	*create_threads(t_philo **philos,
						int *args, t_fork *forks, t_end *end)
{
	int				i;
	pthread_mutex_t	*print_mutex;

	i = 0;
	*philos = ft_calloc(args[0], sizeof(t_philo));
	if (!*philos)
		return (NULL);
	print_mutex = set_philos(*philos, args, forks, end);
	print_log(NULL, 0, NULL);
	while (i < args[0])
	{
		pthread_create(&((*philos)[i].thread),
			NULL, start_routine, &(*philos)[i]);
		i++;
	}
	return (print_mutex);
}
