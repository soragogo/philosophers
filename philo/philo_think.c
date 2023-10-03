/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:20 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 18:28:53 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_think(t_philo *philo)
{
	unsigned long	time;

	time = get_time();
	printf("%lu %d is thinking\n", time, philo->name + 1);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_eat)
			if (is_fork_available(philo) == true)
				break ;
		if (time > philo->time_to_die)
		{
			return (1);
		}
	}
	return (0);
}
