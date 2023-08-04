/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:49:02 by ekamada           #+#    #+#             */
/*   Updated: 2023/08/04 09:49:51 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int error_handling(int ac, char *av[])
{
	if (ac != 5 && ac != 6)
		return (1);
	else if (ft_ispositive(ac, av) == 1)
		return (1);
	else
		return (0);
}
