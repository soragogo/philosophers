#include "philo.h"

void take_forks(t_philo *philo)
{
	unsigned long time;
	pthread_mutex_lock(&(philo->my_fork[0]->lock));
	while ((philo->my_fork[0]->evenodd % 2) ^ (philo->name % 2))
		usleep(1);
	time = get_time();
	// printf("%lu %d has taken a fork[%d]\n", time, philo->name, philo->my_fork[0]->num);
	printf("%lu %d has taken a fork\n", time, philo->name);
	pthread_mutex_lock(&(philo->my_fork[1]->lock));
	while ((philo->my_fork[1]->evenodd % 2) ^ (philo->name % 2))
		usleep(1);
	time = get_time();
	// printf("%lu %d has taken a fork[%d]\n", time, philo->name, philo->my_fork[1]->num);
	printf("%lu %d has taken a fork\n", time, philo->name);
}

void return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->my_fork[0]->lock));
	pthread_mutex_unlock(&(philo->my_fork[1]->lock));
}

int action_eat(t_philo *philo)
{
	unsigned long time;

	take_forks(philo);
	time = get_time();
	philo->time_to_die = time + philo->die_duration;
	philo->time_to_sleep = time + philo->eat_duration;
	printf("%lu %d is eating\n", time, philo->name);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_die)
		{
			printf("%lu %u died\n", time, philo->name);
			return 1;
		}
		if (time > philo->time_to_sleep)
		{
			philo->my_fork[0]->evenodd ^= 1;
			philo->my_fork[1]->evenodd ^= 1;
			return_forks(philo);
			break;
		}
	}
	return 0;
}

int action_sleep(t_philo *philo)
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
		if (time > philo->time_to_die)
		{
			printf("%lu %u died\n", time, philo->name);
			return 1;
		}
	}
	return 0;
}

int action_think(t_philo *philo)
{
	unsigned long time;

	time = get_time();
	printf("%lu %d is thinking\n", time, philo->name);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_eat)
			break;
		if (time > philo->time_to_die)
		{
			printf("%lu %u died\n", time, philo->name);
			return 1;
		}
	}
	return 0;
}

bool everyone_is_alive(t_philo *philo)
{
	bool result;

	result = false;
	pthread_mutex_lock(&(philo->end_flag->lock));
	if (philo->end_flag->flag == 0)
		result = true;
	pthread_mutex_unlock(&(philo->end_flag->lock));
	return (result);
}

void death_certificate(t_philo *philo)
{
	pthread_mutex_lock(&(philo->end_flag->lock));
	philo->end_flag->flag = 1;
	pthread_mutex_unlock(&(philo->end_flag->lock));
}

int philo_actions(t_philo *philo)
{
	unsigned long time;
	time = get_time();
	philo->time_to_die = time;
	while (1)
	{
		if (everyone_is_alive(philo) == false)
			break;

		if (everyone_is_alive(philo) == true)
			if (action_eat(philo) == 1)
			{
				death_certificate(philo);
				return 0;
			}
		if (everyone_is_alive(philo) == true)
			if (action_sleep(philo) == 1)
			{
				death_certificate(philo);
				return 0;
			}
		if (everyone_is_alive(philo) == true)
			if (action_think(philo) == 1)
			{
				death_certificate(philo);
				return 0;
			}
	}
	return 0;
}
