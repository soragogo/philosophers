/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:26:13 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/08 12:22:49 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_log(char *message, int name,
	t_philo *philo, unsigned long start_time)
{
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

void	print_log(char *message, int name, t_philo *philo)
{
	static unsigned long	start_time;

	if (start_time == 0)
		start_time = get_time();
	else
		output_log(message, name, philo, start_time);
}
