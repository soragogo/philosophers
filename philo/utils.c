#include "philo.h"

bool should_continue(t_philo *philo)
{
	bool result;

	result = false;
	pthread_mutex_lock(&(philo->end_flag->lock));
	if ((philo->end_flag->death == 0 && philo->end_flag->eatenup == 0) || (philo->meals_to_eat > 0))
		result = true;
	pthread_mutex_unlock(&(philo->end_flag->lock));
	return (result);
}

void death_certificate(t_philo *philo)
{
	unsigned long time;
	pthread_mutex_lock(&(philo->end_flag->lock));
	time = get_time();
	if (philo->end_flag->death != 1)
		printf("%lu %u died\n", time, philo->name + 1);
	philo->end_flag->death = 1;
	pthread_mutex_unlock(&(philo->end_flag->lock));
}

void set_eatenup_flag(t_philo *philo)
{
	pthread_mutex_lock(&(philo->end_flag->lock));
	philo->end_flag->eatenup = 1;
	pthread_mutex_unlock(&(philo->end_flag->lock));
}

unsigned long get_time()
{
	struct timeval tv;
	unsigned long time;
	time = 0.0;
	gettimeofday(&tv, NULL);
	time += (tv.tv_sec * 1000);
	time += (tv.tv_usec / 1000);

	return time;
}
