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
        i++;
    }
    return forks;
}

t_philo *create_threads(t_philo *list, int *args, t_fork *forks)
{
    int i;

    i = 0;
    list = calloc(args[0], sizeof(t_philo));
    if (!list)
        return (NULL);
    while (i < args[0])
    {
        list[i].name = i;
        pthread_create(&(list[i].thread), NULL, start_routine, &list[i]);
        list[i].my_fork[0] = &forks[i];
        if (i + 1 < args[0])
            list[i].my_fork[1] = &forks[i + 1];
        else
            list[i].my_fork[1] = &forks[0];
        pthread_join(list[i].thread, NULL);
        i++;
    }
    return list;
}

int main(int ac, char *av[])
{
    t_philo *list = NULL;
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
    list = create_threads(list, args, forks);
    for (int i = 0; i < 5; i++)
        printf("args[%d] :%d\n", i, args[i]);

    free(forks);
    free(list);
    return 0;
}
