/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:29:42 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/04 11:31:50 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_philo *philo, t_fork **left_fork_address)
{
	pthread_mutex_lock(&(philo->fork[LEFT]->lock));
	*left_fork_address = philo->fork[LEFT];
	if (philo->fork[LEFT]->prev != philo->name && philo->fork[LEFT]->ready)
		philo->fork[LEFT]->ready = false;
	else
	{
		pthread_mutex_unlock(&(philo->fork[LEFT]->lock));
		return (2);
	}
	pthread_mutex_unlock(&(philo->fork[LEFT]->lock));
	return (0);
}

int	take_right_fork(t_philo *philo, t_fork **left_fork_address)
{
	pthread_mutex_lock(&(philo->fork[RIGHT]->lock));
	if (*left_fork_address == philo->fork[RIGHT])
	{
		pthread_mutex_unlock(&(philo->fork[RIGHT]->lock));
		print_log("has taken a fork", philo->name + 1, philo);
		return (1);
	}
	else if (philo->fork[RIGHT]->prev != philo->name
		&& philo->fork[RIGHT]->ready)
	{
		philo->fork[RIGHT]->ready = false;
		pthread_mutex_unlock(&(philo->fork[RIGHT]->lock));
		print_log("has taken a fork", philo->name + 1, philo);
		print_log("has taken a fork", philo->name + 1, philo);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&(philo->fork[RIGHT]->lock));
		pthread_mutex_lock(&(philo->fork[LEFT]->lock));
		philo->fork[LEFT]->ready = true;
		pthread_mutex_unlock(&(philo->fork[LEFT]->lock));
		return (2);
	}
}

int	take_forks(t_philo *philo, int num_of_forks)
{
	t_fork	*left_fork_address;
	int		ret;

	if (num_of_forks == 1)
		return (1);
	left_fork_address = NULL;
	ret = take_left_fork(philo, &left_fork_address);
	if (ret == 0)
	{
		ret = take_right_fork(philo, &left_fork_address);
	}
	return (ret);
}

void	return_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork[LEFT]->lock));
	philo->fork[LEFT]->prev = philo->name;
	philo->fork[LEFT]->ready = true;
	pthread_mutex_unlock(&(philo->fork[LEFT]->lock));
	pthread_mutex_lock(&(philo->fork[RIGHT]->lock));
	philo->fork[RIGHT]->prev = philo->name;
	philo->fork[RIGHT]->ready = true;
	pthread_mutex_unlock(&(philo->fork[RIGHT]->lock));
}

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
