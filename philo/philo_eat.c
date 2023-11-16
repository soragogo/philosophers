/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:29:42 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/08 12:24:43 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_arrangement(t_philo *philo)
{
	int	num_of_forks;

	num_of_forks = 0;
	while (take_forks(philo, num_of_forks))
	{
		if (!should_continue(philo))
			return (0);
		if (get_time() > philo->time_to_die)
			return (1);
	}
	philo->time_to_die = get_time() + philo->die_duration;
	philo->time_to_sleep = get_time() + philo->eat_duration;
	if (!should_continue(philo))
	{
		return_forks(philo);
		return (0);
	}
	return (2);
}

int	action_eat(t_philo *philo)
{
	int	arrange_result;

	arrange_result = (eat_arrangement(philo));
	if (arrange_result != 2)
		return (arrange_result);
	print_log("is eating", philo->name + 1, philo);
	while (1)
	{
		if (get_time() > philo->time_to_die)
		{
			return_forks(philo);
			return (1);
		}
		if (get_time() > philo->time_to_sleep)
		{
			return_forks(philo);
			break ;
		}
		usleep(300);
	}
	return (0);
}
