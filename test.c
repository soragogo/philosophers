/* ************************************************************************** *//*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:54:16 by ekamada           #+#    #+#             */
/*   Updated: 2023/08/04 14:32:27 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_routine(void *arg)
{
	int *p = (int *)arg;
	usleep(30);
	// for (int i = 0; i < 100; i++)
	printf("%d\n", *p);
}
void *ststst_routine(void *arg)
{
	// for (int i = 0; i < 100; i++)
	printf("------------\n");
}

int main(int ac, char *av[])
{
	t_list *list;
	pthread_t thread1;
	pthread_t thread2;
	int args[5];
	int a = 1;
	if (error_handling(ac, av, &args) != 0)
	{
		write(1,"Error\n",6);
		exit(1);
	}
	pthread_create(&thread1, NULL, start_routine, &a);
	pthread_create(&thread2, NULL, ststst_routine, &a);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	for (int i = 0 ; i < 5; i++)
		printf("args[%d] :%d\n", i, args[i]);
}
