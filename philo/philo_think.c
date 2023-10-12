/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:20 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/12 14:43:11 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_think(t_philo *philo)
{
	unsigned long	time;
	bool			fork_ready;

	fork_ready = false;
	if (!should_continue(philo))
		return (0);
	printf("%lu %d is thinking\n", get_time(), philo->name + 1);
	while (1)
	{
		time = get_time();
		if (!fork_ready && is_fork_available(philo))
			fork_ready = true;
		if (time > philo->time_to_eat && fork_ready)
			break ;
		if (time > philo->time_to_die)
			return (1);
		usleep(100);
	}
	return (0);
}
