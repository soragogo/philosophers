int philo_is_eating(int time_to_eat)
{
	int start_eating;
	int 
}

int philo_is_thinking(int time_to_eat)
{
}



int philo_is_sleeping(int time_to_sleep, t_philo philo)
{
	int started_sleep = currentTime
	printf("%d %d is sleeping\n", currentTime, philo.name);
	while(currentTime.tv_usec - started_sleep > time_to_sleep*1000)
	{
		if (currentTime.tv_usec / 1000 >= philo.longevity)
		{
			printf("%d %d died\n", philo.name);
			return (1);
		}


	}
	return (0);
}
