/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:09 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/03 22:23:56 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	execute_action(int (*action)(t_philo*), t_philo *philo)
{
	if (should_continue(philo))
	{
		if (action(philo) == 1)
		{
			death_certificate(philo);
			return (0);
		}
	}
	return (1);
}

int	philo_actions(t_philo *philo)
{
	philo->time_to_die = get_time() + philo->die_duration;
	if (philo->name % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!execute_action(action_eat, philo))
			return (0);
		if (!execute_action(action_sleep, philo))
			return (0);
		if (!execute_action(action_think, philo))
			return (0);
		if (!should_continue(philo))
			break ;
	}
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_actions(philo);
	return (NULL);
}
