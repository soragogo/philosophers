/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:26:13 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/03 22:55:21 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_continue(t_philo *philo)
{
	bool	result;

	result = false;
	if (philo->meals_to_eat == -1)
	{
		pthread_mutex_lock(&(philo->end_flag->lock));
		if (philo->end_flag->death == 0)
			result = true;
		pthread_mutex_unlock(&(philo->end_flag->lock));
	}
	else
	{
		pthread_mutex_lock(&(philo->end_flag->lock));
		if (philo->end_flag->death == 1)
			result = false;
		else if ((philo->end_flag->eatenup == 0 || philo->meals_to_eat > 0))
			result = true;
		pthread_mutex_unlock(&(philo->end_flag->lock));
	}
	return (result);
}

void	death_certificate(t_philo *philo)
{
	bool	should_print_certificate;

	should_print_certificate = false;
	pthread_mutex_lock(&(philo->end_flag->lock));
	if (philo->end_flag->death != 1)
		should_print_certificate = true;
	philo->end_flag->death = 1;
	pthread_mutex_unlock(&(philo->end_flag->lock));
	if (should_print_certificate)
		print_log("died", philo->name + 1, philo);
}

void	set_eatenup_flag(t_philo *philo)
{
	pthread_mutex_lock(&(philo->end_flag->lock));
	philo->end_flag->eatenup = 1;
	pthread_mutex_unlock(&(philo->end_flag->lock));
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	time = 0;
	gettimeofday(&tv, NULL);
	time += (tv.tv_sec * 1000);
	time += (tv.tv_usec / 1000);
	return (time);
}

void	print_log(char *message, int name, t_philo *philo)
{
	static unsigned long	start_time;

	if (start_time == 0)
	{
		start_time = get_time();
		return ;
	}
	if (ft_strlen(message) == 4)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("%lu %d %s\n", get_time() - start_time, name, message);
		pthread_mutex_unlock(philo->print_mutex);
	}
	else if (should_continue(philo) == true)
	{
		pthread_mutex_lock(&(philo->end_flag->lock));
		if (philo->end_flag->death == 0)
		{
			pthread_mutex_unlock(&(philo->end_flag->lock));
			pthread_mutex_lock(philo->print_mutex);
			printf("%lu %d %s\n", get_time() - start_time, name, message);
			pthread_mutex_unlock(philo->print_mutex);
		}
		else
			pthread_mutex_unlock(&(philo->end_flag->lock));
	}
}
