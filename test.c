#include "philo.h"

void *start_routine(void *arg)
{
    int *p = (int *)arg;
    usleep(30);
    printf("%d\n", *p);
}

int     *create_forks(int num_of_philos)
{
    int     *forks;
    int     i;

    i = 0;
    forks = malloc(sizeof(int)* num_of_philos);
    if (!forks)
        return (NULL);
    while (i < num_of_philos)
    {
        forks[i] = 1;
        i++;
    }
    return forks;  
}

t_list *create_threads(t_list *list, int *args, int *forks)
{
    int     i;

    i = 0;  
    list = malloc(sizeof(t_list) * args[0]);
    if (!list)
        return (NULL);
    while (i < args[0])
    {
        list[i].philo = i;
        pthread_create(&(list[i].thread), NULL, start_routine, &(forks[i]));
        list[i].my_fork[0] = &forks[i];
        if (i + 1 < args[0])
            list[i].my_fork[1] = &forks[i + 1];
        else
            list[i].my_fork[1] = &forks[0];  // add circularity for the last philosopher's right fork
        pthread_join(list[i].thread, NULL);
        i++;
    }
    return list;
}

int main(int ac, char *av[])
{
    t_list *list = NULL;
    int     args[5];
    int     *forks;
    if (error_handling(ac, av, &args) != 0)
    {
        write(1,"Error\n",6);
        return (1);
    }
    forks = create_forks(args[0]);
    if (!forks)
        return (1);
    list = create_threads(list, args, forks);
    for (int i = 0 ; i < 5; i++)
        printf("args[%d] :%d\n", i, args[i]);

    free(forks); // deallocate memory
    free(list);  // deallocate memory
    return 0;
}

