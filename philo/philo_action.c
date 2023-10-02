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
//!=でよくない？
// mutex_lockしちゃってるからこれだと待ってても他の人がさわれないから書きかわらなくない？

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
			if (philo->meals_to_eat > 0)
				philo->meals_to_eat--;
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
	printf("%lu %d is sleeping\n", time, philo->name + 1);
	usleep(philo->sleep_duration * 950);
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

int action_think(t_philo *philo, int right, int left)
{
	unsigned long time;
	time = get_time();
	if (time > philo->time_to_eat)
		if (is_fork_available(philo, right, left) == true)
			return 0;
	printf("%lu %d is thinking\n", time, philo->name + 1);
	while (1)
	{
		time = get_time();
		if (time > philo->time_to_eat)
			if (is_fork_available(philo, right, left) == true)
				break;

		if (time > philo->time_to_die)
		{
			printf("%lu %u died\n", time, philo->name + 1);
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

void set_right_left(t_philo *philo, int *right, int *left)
{
	if (philo->name % 2 == 0)
	{
		*right = 1;
		*left = 0;
	}
	else
	{
		*right = 1;
		*left = 0;
	}
}

int philo_actions(t_philo *philo)
{
	unsigned long time;
	int right;
	int left;

	set_right_left(philo, &right, &left);
	time = get_time();
	philo->time_to_die = time + philo->die_duration;
	while (1)
	{
		if (everyone_is_alive(philo) == false)
			break;
		if (everyone_is_alive(philo) == true)
			if (action_think(philo, right, left) == 1)
			{
				death_certificate(philo);
				return 0;
			}
		if (everyone_is_alive(philo) == true)
			if (action_eat(philo, right, left) == 1)
			{
				death_certificate(philo);
				return 0;
			}
		if (philo->meals_to_eat == 0)
			return 0;
		if (everyone_is_alive(philo) == true)
			if (action_sleep(philo) == 1)
			{
				death_certificate(philo);
				return 0;
			}
	}
	return 0;
}
