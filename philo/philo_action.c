/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:09 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/03 18:34:14 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_actions(t_philo *philo)
{
	unsigned long	time;

	time = get_time();
	philo->time_to_die = time + philo->die_duration;
	while (1)
	{
		if (should_continue(philo) == false)
			break ;
		if (should_continue(philo) == true)
		{
			if (action_think(philo) == 1)
			{
				death_certificate(philo);
				return (0);
			}
		}
		if (should_continue(philo) == true)
		{
			if (action_eat(philo) == 1)
			{
				death_certificate(philo);
				return (0);
			}
		}
		if (should_continue(philo) == true)
		{
			if (action_sleep(philo) == 1)
			{
				death_certificate(philo);
				return (0);
			}
		}
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
