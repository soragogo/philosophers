/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:33:43 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/03 18:46:06 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (number > (INT_MAX - str[i] + '0') / 10)
		{
			printf("number : %d\n", INT_MAX - str[i] + '0');
			return (-1);
		}
		number = number * 10 + str[i] - '0';
		i++;
	}
	return (number);
}
