/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:29:42 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/12 14:29:52 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if ((philo->fork[0]->prev) != (philo->name))
	{
		pthread_mutex_lock(&(philo->fork[0]->lock));
		philo->fork[0]->ready = false;
		pthread_mutex_unlock(&(philo->fork[0]->lock));
		if ((philo->fork[1]->prev) != (philo->name) && should_continue(philo))
		{
			pthread_mutex_lock(&(philo->fork[1]->lock));
			philo->fork[1]->ready = false;
			pthread_mutex_unlock(&(philo->fork[1]->lock));
			printf("%lu %d has taken a fork\n", get_time(), philo->name + 1);
			printf("%lu %d has taken a fork\n", get_time(), philo->name + 1);
			return (0);
		}
		else
		{
			pthread_mutex_lock(&(philo->fork[0]->lock));
			philo->fork[0]->ready = true;
			pthread_mutex_unlock(&(philo->fork[0]->lock));
		}
	}
	return (1);
}

bool	is_fork_available(t_philo *philo)
{
	if (philo->fork[0]->prev != philo->name && philo->fork[0]->ready)
	{
		pthread_mutex_lock(&(philo->fork[0]->lock));
		philo->fork[0]->ready = false;
		pthread_mutex_unlock(&(philo->fork[0]->lock));
		if (philo->fork[1]->prev != philo->name && philo->fork[1]->ready)
		{
			pthread_mutex_lock(&(philo->fork[1]->lock));
			philo->fork[1]->ready = false;
			pthread_mutex_unlock(&(philo->fork[1]->lock));
			return (true);
		}
		else
		{
			pthread_mutex_lock(&(philo->fork[0]->lock));
			philo->fork[0]->ready = true;
			pthread_mutex_unlock(&(philo->fork[0]->lock));
		}
	}
	return (false);
}

void	return_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork[0]->lock));
	philo->fork[0]->prev = philo->name;
	philo->fork[0]->ready = true;
	pthread_mutex_unlock(&(philo->fork[0]->lock));
	pthread_mutex_lock(&(philo->fork[1]->lock));
	philo->fork[1]->prev = philo->name;
	philo->fork[1]->ready = true;
	pthread_mutex_unlock(&(philo->fork[1]->lock));
}

int	eat_arrangement(t_philo *philo)
{
	while (take_forks(philo))
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
	printf("%lu %d is eating\n", get_time(), philo->name + 1);
	usleep(philo->eat_duration * 900);
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
		usleep(100);
	}
	return (0);
}
