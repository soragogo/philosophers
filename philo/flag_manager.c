/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:26:13 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/04 12:15:13 by ekamada          ###   ########.fr       */
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
