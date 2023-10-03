/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:11:31 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/03 19:55:49 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*str;
	size_t		memory;

	if (count == 0 || size == 0)
		memory = 1;
	else
	{
		if (size * count / count != size)
			return (NULL);
		memory = size * count;
	}
	str = (void *)malloc(memory);
	if (str == NULL)
		return (NULL);
	return (ft_bzero(str, memory));
}
