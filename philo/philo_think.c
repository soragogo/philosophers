#include "philo.h"

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
