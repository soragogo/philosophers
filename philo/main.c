#include "philo.h"

void *start_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    unsigned long time;
    bool is_alive = true;

    while (1)
    {
        philo_actions(philo, &is_alive);
        if (is_alive == false)
        {
            time = get_time();
            printf("%lu %u died\n", time, philo->name);
            break;
        }
    }
    return NULL;
}

t_fork *create_forks(int num_of_philos)
{
    t_fork *forks;
    int i;

    i = 0;
    forks = calloc(num_of_philos, sizeof(t_fork));
    if (!forks)
        return (NULL);
    while (i < num_of_philos)
    {
        forks[i].is_available = true;
        i++;
    }
    return forks;
}

t_philo *create_threads(t_philo *philos, int *args, t_fork *forks)
{
    int i;

    i = 0;
    philos = calloc(args[0], sizeof(t_philo));
    if (!philos)
        return (NULL);
    while (i < args[0])
    {
        philos[i].name = i;
        pthread_create(&(philos[i].thread), NULL, start_routine, &philos[i]);
        philos[i].my_fork[0] = &forks[i];
        if (i + 1 < args[0])
            philos[i].my_fork[1] = &forks[i + 1];
        else
            philos[i].my_fork[1] = &forks[0];
        philos[i].die_duration = args[1];
        philos[i].eat_duration = args[2];
        philos[i].sleep_duration = args[3];

        i++;
    }
    return philos;
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

int main(int ac, char *av[])
{
    t_philo *philos = NULL;
    int args[5];
    t_fork *forks;
    if (error_handling(ac, av, &args) != 0)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    forks = create_forks(args[0]);
    if (!forks)
        return (1);
    philos = create_threads(philos, args, forks);
    for (int i = 0; i < 5; i++)
    {
        printf("args[%d] :%d\n", i, args[i]);
        pthread_join(philos[i].thread, NULL);
    }

    free(forks);
    free(philos);
    return 0;
}
