/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:33:43 by ekamada           #+#    #+#             */
/*   Updated: 2023/07/11 22:45:48 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
int ft_atoi(int *error_num, char *str)
{
	int i;
	int number;
	int minus;

	i = 0;
	number = 0;
	minus = 1;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	if (ft_strcmp(str, "-2147483648") == 0)
		return (INT_MIN);
	while (str[i])
	{
		if (number > INT_MAX / 10)
			*error_num = 1;
		number *= 10;
		if (number > INT_MAX - str[i] + '0')
			*error_num = 1;
		number = number + str[i] - '0';
		i++;
	}
	return (minus * number);
}
