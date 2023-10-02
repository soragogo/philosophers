/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soma <soma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:49:02 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/02 17:11:50 by soma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 本家のisdigitは数字だったら１を返す。ここでは数字だったら０を返す。読みにくい

int ft_isdigit(int c, int j)
{
	if (j == 0)
	{
		if ((c <= '9' && c >= '1'))
			return (0);
	}
	else if (c <= '9' && c >= '0')
		return (0);
	return (1);
}
int ft_ispositive(int ac, char *av[])
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j], j) == 1)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
// なんのためのargsダブルポインタ？
int error_handling(int ac, char *av[], int (*args)[5])
{
	int i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	else if (ft_ispositive(ac, av) == 1)
		return (1);
	else
	{
		while (i < ac - 1)
		{
			(*args)[i] = ft_atoi(av[i + 1]);
			if ((*args)[i] == -1)
				return (1);
			i++;
		}
		if (ac == 5)
			(*args)[4] = 0;
		return (0);
	}
}
