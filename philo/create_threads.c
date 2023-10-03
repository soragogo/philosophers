/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:44:59 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 18:45:00 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_threads(t_philo *philos, int *args, t_fork *forks, t_end *end)
{
	int	i;

	i = 0;
	philos = calloc(args[0], sizeof(t_philo));
	if (!philos)
		return (NULL);
	while (i < args[0])
	{
		philos[i].name = i;
		if (args[4])
			philos[i].meals_to_eat = args[4] + 1;
		else
			philos[i].meals_to_eat = -1;
		philos[i].end_flag = end;
		philos[i].my_fork[0] = &forks[i];
		if (i + 1 < args[0])
			philos[i].my_fork[1] = &forks[i + 1];
		else
			philos[i].my_fork[1] = &forks[0];
		philos[i].die_duration = args[1];
		philos[i].eat_duration = args[2];
		philos[i].sleep_duration = args[3];
		i++;
	}
	i = 0;
	while (i < args[0])
	{
		pthread_create(&(philos[i].thread), NULL, start_routine, &philos[i]);
		i++;
	}
	return (philos);
}
