/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:34:27 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/16 18:26:53 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ending_operation(t_philo *philos, t_fork *forks, int num, t_end *end)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&(forks[i].lock));
		i++;
	}
	pthread_mutex_destroy(&(end->lock));
	free(forks);
	free(philos);
}

void	init_end_flag(t_end *end)
{
	pthread_mutex_init(&(end->lock), NULL);
	end->death = 0;
	end->eatenup = 0;
}

int	main(int ac, char *av[])
{
	t_philo			*philos;
	int				args[5];
	t_fork			*forks;
	t_end			end;
	pthread_mutex_t	*print_mutex;

	philos = NULL;
	if (ac == 6 && ft_strncmp(av[5], "0", 2) == 0)
		return (0);
	ft_bzero(args, sizeof(args));
	if (error_handling(ac, av, &args) != 0)
		return (1);
	init_end_flag(&end);
	forks = create_forks(args[0]);
	if (!forks)
		return (1);
	print_mutex = create_threads(&philos, args, forks, &end);
	if (!philos)
		return (1);
	ending_operation(philos, forks, args[0], &end);
	pthread_mutex_destroy(print_mutex);
	free(print_mutex);
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }
