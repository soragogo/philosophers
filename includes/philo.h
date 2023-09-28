/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:01:06 by emukamada         #+#    #+#             */
/*   Updated: 2023/08/03 11:01:11 by emukamada        ###   ########.fr       */
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
typedef struct s_list
{
	unsigned int	name;
	pthread_t	thread;
	int		*my_fork[2];
    int     longevity;

} t_philo;
int	error_handling(int ac, char *av[], int (*args)[5]);
int	ft_atoi(char *str);
#endif
