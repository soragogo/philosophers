#include "philo.h"

void *start_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    philo_actions(philo);
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
        pthread_mutex_init(&(forks[i].lock), NULL);
        forks[i].is_available = true;
        // forks[i].num = i;
        forks[i].evenodd = 0;
        i++;
    }
    return forks;
}

t_philo *create_threads(t_philo *philos, int *args, t_fork *forks, t_end *end)
{
    int i;

    i = 0;
    philos = calloc(args[0], sizeof(t_philo));
    if (!philos)
        return (NULL);
    while (i < args[0])
    {
        philos[i].name = i;
        philos[i].end_flag = end;
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
    i = 0;
    while (i < args[0])
    {
        pthread_create(&(philos[i].thread), NULL, start_routine, &philos[i]);
        // pthread_detach(philos[i].thread); detachするとメインがthreadの終了を待たない
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
    t_end end;
    int i = 0;

    if (error_handling(ac, av, &args) != 0)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    forks = create_forks(args[0]);
    if (!forks)
        return (1);
    pthread_mutex_init(&(end.lock), NULL);
    end.flag = 0;
    philos = create_threads(philos, args, forks, &end);
    while (i < args[0])
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    free(forks);
    free(philos);

    return 0;
}
