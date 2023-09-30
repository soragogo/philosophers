#include "philo.h"

void action_eat(t_philo *philo, bool *is_alive)
{
	unsigned long time;

	time = get_time();
	philo->time_to_die = time + philo->eat_duration;
	philo->time_to_sleep = time + philo->eat_duration;
	printf("%lu %d is eating\n", time, philo->name);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_sleep)
			break;
	}
	*is_alive = true;
}

void action_sleep(t_philo *philo, bool *is_alive)
{
	unsigned long time;

	time = get_time();
	philo->time_to_think = time + philo->sleep_duration;
	printf("%lu %d is sleeping\n", time, philo->name);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_think)
			break;
	}
	*is_alive = false;
}

void action_think(t_philo *philo, bool *is_alive)
{
	unsigned long time;

	time = get_time();
	printf("%lu %d is thinking\n", time, philo->name);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_eat)
			break;
	}
	*is_alive = false;
}

// int action_sleep(int time_to_sleep, t_philo philo)
// {
// 	int started_sleep = currentTime
// 		printf("%d %d is sleeping\n", currentTime, philo.name);
// 	while (currentTime.tv_usec - started_sleep > time_to_sleep * 1000)
// 	{
// 		if (currentTime.tv_usec / 1000 >= philo.longevity)
// 		{
// 			printf("%d %d died\n", philo.name);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int philo_actions(t_philo *philo, bool *is_alive)
{
	while (1)
	{
		action_eat(philo, is_alive);
		if (is_alive == false)
			break;
		action_think(philo, is_alive);
		if (is_alive == false)
			break;
		action_sleep(philo, is_alive);
		if (is_alive == false)
			break;
	}

	return 0;
}
