/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:29:08 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/11 22:31:00 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_sleep(t_philo *philo)
{
	unsigned long	time;

	if (philo->meals_to_eat > 0)
	{
		philo->meals_to_eat--;
		if (philo->meals_to_eat == 0)
			set_eatenup_flag(philo);
	}
	time = get_time();
	philo->time_to_think = time + philo->sleep_duration;
	printf("%lu %d is sleeping\n", time, philo->name + 1);
	usleep(philo->sleep_duration * 950);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_think)
			break ;
		if (time > philo->time_to_die)
		{
			return (1);
		}
		usleep(100);
	}
	return (0);
}
