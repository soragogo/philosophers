#include "philo.h"
int take_forks(t_philo *philo, int right, int left)
{
	unsigned long time;
	pthread_mutex_lock(&(philo->my_fork[right]->lock));
	if ((philo->my_fork[right]->history) != (philo->name))
	{
		philo->my_fork[right]->is_available = false;
		pthread_mutex_unlock(&(philo->my_fork[right]->lock));
		pthread_mutex_lock(&(philo->my_fork[left]->lock));
		if ((philo->my_fork[left]->history) != (philo->name))
		{
			time = get_time();
			philo->my_fork[left]->is_available = false;
			printf("%lu %d has taken a fork\n", time, philo->name + 1);
			printf("%lu %d has taken a fork\n", time, philo->name + 1);
			pthread_mutex_unlock(&(philo->my_fork[left]->lock));
			return 0;
		}
		else
		{
			pthread_mutex_lock(&(philo->my_fork[right]->lock));
			philo->my_fork[right]->is_available = true;
			pthread_mutex_unlock(&(philo->my_fork[right]->lock));
			return 1;
		}
		pthread_mutex_unlock(&(philo->my_fork[left]->lock));
		return 1;
	}
	return 1;
}

bool is_fork_available(t_philo *philo, int right, int left)
{
	bool result;
	result = false;

	pthread_mutex_lock(&(philo->my_fork[right]->lock));
	if ((philo->my_fork[right]->history) != (philo->name))
	{
		if (philo->my_fork[right]->is_available == true)
		{
			philo->my_fork[right]->is_available = false;
			pthread_mutex_unlock(&(philo->my_fork[right]->lock));
			pthread_mutex_lock(&(philo->my_fork[left]->lock));
			// printf("history: %d\n", philo->my_fork[left]->history);
			if ((philo->my_fork[left]->history) != (philo->name))
				if (philo->my_fork[left]->is_available == true)
					result = true;
			pthread_mutex_unlock(&(philo->my_fork[left]->lock));
		}
		else
			pthread_mutex_unlock(&(philo->my_fork[right]->lock));
	}
	else
		pthread_mutex_unlock(&(philo->my_fork[right]->lock));
	return result;
}

void return_forks(t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&(philo->my_fork[right]->lock));
	pthread_mutex_lock(&(philo->my_fork[left]->lock));
	philo->my_fork[right]->history = philo->name;
	philo->my_fork[left]->history = philo->name;
	philo->my_fork[right]->is_available = true;
	philo->my_fork[left]->is_available = true;
	pthread_mutex_unlock(&(philo->my_fork[right]->lock));
	pthread_mutex_unlock(&(philo->my_fork[left]->lock));
}

int action_eat(t_philo *philo, int right, int left)
{
	unsigned long time;

	while (take_forks(philo, right, left))
	{
		time = get_time();
		if (time > philo->time_to_die)
		{
			printf("%lu %u died\n", time, philo->name);
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
			return_forks(philo, right, left);
			printf("%lu %u died\n", time, philo->name);
			return 1;
		}
		if (time > philo->time_to_sleep)
		{
			return_forks(philo, right, left);
			break;
		}
	}
	return 0;
}
