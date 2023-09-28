#include "philo.h"

void *start_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    struct timeval tv;

    usleep(300);
    for (int i = 0; i < 1000; i++)
    {

        gettimeofday(&tv, NULL);
        usleep(20);
        // printf("%d\n", tv.tv_usec);
    }
    printf("%d\n", p->time_to_die);
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
        pthread_mutex_init(&(forks[i].lock), NULL);
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
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    return philos;
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
        printf("args[%d] :%d\n", i, args[i]);

    free(forks);
    free(philos);
    return 0;
}
