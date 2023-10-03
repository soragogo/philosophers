#include "philo.h"
int take_forks(t_philo *philo)
{
	unsigned long time;
	pthread_mutex_lock(&(philo->my_fork[0]->lock));
	if ((philo->my_fork[0]->history) != (philo->name))
	{
		philo->my_fork[0]->is_available = false;
		pthread_mutex_unlock(&(philo->my_fork[0]->lock));
		pthread_mutex_lock(&(philo->my_fork[1]->lock));
		if ((philo->my_fork[1]->history) != (philo->name))
		{
			time = get_time();
			philo->my_fork[1]->is_available = false;
			printf("%lu %d has taken a fork\n", time, philo->name + 1);
			printf("%lu %d has taken a fork\n", time, philo->name + 1);
			pthread_mutex_unlock(&(philo->my_fork[1]->lock));
			return 0;
		}
		else
		{
			pthread_mutex_lock(&(philo->my_fork[0]->lock));
			philo->my_fork[0]->is_available = true;
			pthread_mutex_unlock(&(philo->my_fork[0]->lock));
			return 1;
		}
		pthread_mutex_unlock(&(philo->my_fork[1]->lock));
		return 1;
	}
	return 1;
}

bool is_fork_available(t_philo *philo)
{
	bool result;
	result = false;

	pthread_mutex_lock(&(philo->my_fork[0]->lock));
	if ((philo->my_fork[0]->history) != (philo->name))
	{
		if (philo->my_fork[0]->is_available == true)
		{
			philo->my_fork[0]->is_available = false;
			pthread_mutex_unlock(&(philo->my_fork[0]->lock));
			pthread_mutex_lock(&(philo->my_fork[1]->lock));
			// printf("history: %d\n", philo->my_fork[1]->history);
			if ((philo->my_fork[1]->history) != (philo->name))
				if (philo->my_fork[1]->is_available == true)
					result = true;
			pthread_mutex_unlock(&(philo->my_fork[1]->lock));
		}
		else
			pthread_mutex_unlock(&(philo->my_fork[0]->lock));
	}
	else
		pthread_mutex_unlock(&(philo->my_fork[0]->lock));
	return result;
}

void return_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->my_fork[0]->lock));
	pthread_mutex_lock(&(philo->my_fork[1]->lock));
	philo->my_fork[0]->history = philo->name;
	philo->my_fork[1]->history = philo->name;
	philo->my_fork[0]->is_available = true;
	philo->my_fork[1]->is_available = true;
	pthread_mutex_unlock(&(philo->my_fork[0]->lock));
	pthread_mutex_unlock(&(philo->my_fork[1]->lock));
}

int action_eat(t_philo *philo)
{
	unsigned long time;

	while (take_forks(philo))
	{
		time = get_time();
		if (time > philo->time_to_die)
		{

			return 1;
		}
	}
	time = get_time();
	philo->time_to_die = time + philo->die_duration;
	philo->time_to_sleep = time + philo->eat_duration;
	printf("%lu %d is eating\n", time, philo->name + 1);
	usleep(philo->eat_duration * 950);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_die)
		{
			return_forks(philo);

			return 1;
		}
		if (time > philo->time_to_sleep)
		{
			return_forks(philo);
			break;
		}
	}
	return 0;
}
