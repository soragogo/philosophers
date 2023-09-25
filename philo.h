/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:01:06 by emukamada         #+#    #+#             */
/*   Updated: 2023/09/25 22:11:42 by ekamada          ###   ########.fr       */
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
	bool is_available;
} t_fork;

typedef struct s_list
{
	unsigned int	philo;
	pthread_t	thread;
	unsigned int time_to_die;
	t_fork		*my_fork[2];

} t_list;


int	error_handling(int ac, char *av[], int (*args)[5]);
int	ft_atoi(char *str);
#endif
