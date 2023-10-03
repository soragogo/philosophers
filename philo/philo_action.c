#include "philo.h"

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
		if (should_continue(philo) == false)
			break;
		if (should_continue(philo) == true)
			if (action_think(philo, right, left) == 1)
			{
				death_certificate(philo);
				return 0;
			}

		if (should_continue(philo) == true)
			if (action_eat(philo, right, left) == 1)
			{
				death_certificate(philo);
				return 0;
			}
		if (should_continue(philo) == true)
			if (action_sleep(philo) == 1)
			{
				death_certificate(philo);
				return 0;
			}
	}
	return 0;
}

void *start_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	philo_actions(philo);
	return NULL;
}
