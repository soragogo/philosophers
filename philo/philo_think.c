/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:20 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/12 18:55:30 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_think(t_philo *philo)
{
	unsigned long	time;
	bool			fork_ready;

	fork_ready = false;
	print_log("is thinking", philo->name + 1, philo);
	while (1)
	{
		if (!fork_ready && is_fork_available(philo))
			fork_ready = true;
		time = get_time();
		if (time > philo->time_to_eat && fork_ready)
			break ;
		if (time > philo->time_to_die)
			return (1);
		usleep(200);
	}
	return (0);
}
