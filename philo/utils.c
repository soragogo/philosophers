/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:26:13 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/04 12:19:45 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




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

void	mutex_and_print(char *message, int name,
	t_philo *philo, unsigned long start_time)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lu %d %s\n", get_time() - start_time, name, message);
	pthread_mutex_unlock(philo->print_mutex);
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
