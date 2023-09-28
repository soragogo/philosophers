#include "philo.h"

void *start_routine(void *arg)
{
    int *p = (int *)arg;
    usleep(30);
    return (p);
}

int *create_forks(int num_of_philos)
{
    int *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(int) * num_of_philos);
    if (!forks)
        return (NULL);
    while (i < num_of_philos)
    {
        forks[i] = 1;
        i++;
    }
    return forks;
}

t_philo *create_threads(t_philo *list, int *args, int *forks)
{
    int i;

    i = 0;
    list = malloc(sizeof(t_philo) * args[0]);
    if (!list)
        return (NULL);
    while (i < args[0])
    {
        list[i].name = i;
        pthread_create(&(list[i].thread), NULL, start_routine, &(forks[i]));
        list[i].my_fork[0] = &forks[i];
        list[i].my_fork[1] = &forks[(i + 1) % args[0]];
        pthread_join(list[i].thread, NULL);
        i++;
    }
    return list;
}

int timestamp(void)
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    printf("Milliseconds: %d\n", currentTime.tv_usec / 1000);

    return 0;
}
int main(int ac, char *av[])
{
    t_philo *list = NULL;
    int args[5];
    int *forks;
    if (error_handling(ac, av, &args) != 0)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    forks = create_forks(args[0]);
    if (!forks)
        return (1);
    list = create_threads(list, args, forks);
    if (!list)
        return (1);

    free(forks);
    free(list);
    return 0;
}
__attribute__((destructor)) static void destructor()
{
    system("leaks -q philosophers");
}
