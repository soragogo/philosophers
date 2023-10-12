/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:29:08 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/12 13:54:46 by emukamada        ###   ########.fr       */
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
	if (!should_continue(philo))
		return (0);
	printf("%lu %d is sleeping\n", time, philo->name + 1);
	usleep(philo->sleep_duration * 900);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_think)
			break ;
		if (time > philo->time_to_die)
			return (1);
		usleep(100);
	}
	return (0);
}
