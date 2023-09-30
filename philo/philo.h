/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:01:06 by emukamada         #+#    #+#             */
/*   Updated: 2023/09/30 18:21:58 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <libc.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t lock;
	bool is_available;
} t_fork;

typedef struct s_philo
{
	unsigned int name;
	pthread_t thread;
	t_fork *my_fork[2];
	int die_duration;
	int eat_duration;
	int sleep_duration;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	unsigned long time_to_think;

} t_philo;

int error_handling(int ac, char *av[], int (*args)[5]);
int ft_atoi(char *str);
int philo_actions(t_philo *philo, bool *is_alive);
unsigned long get_time();
#endif
