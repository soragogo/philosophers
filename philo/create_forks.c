/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:43:57 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/11 23:05:32 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_forks(int num_of_philos)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = ft_calloc(num_of_philos, sizeof(t_fork));
	if (!forks)
		return (NULL);
	while (i < num_of_philos)
	{
		pthread_mutex_init(&(forks[i].lock), NULL);
		forks[i].ready = true;
		forks[i].prev = -1;
		i++;
	}
	return (forks);
}
