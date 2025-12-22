
#include "philo.h"

int cast_args(int argc, char **argv, t_constants *constants)
{
    int i;

    constants->num_philosophers = ft_atoi(argv[1]);
    constants->time_to_die = ft_atoi(argv[2]);
    constants->time_to_eat = ft_atoi(argv[3]);
    constants->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        constants->num_meals = ft_atoi(argv[5]);
    else
        constants->num_meals = -1;
    if (constants->num_philosophers <= 0 || constants->time_to_die < 0 ||
        constants->time_to_eat < 0 || constants->time_to_sleep < 0 ||
        (argc == 6 && constants->num_meals <= 0))
        return (0);
    constants->forks = malloc(sizeof(pthread_mutex_t) * constants->num_philosophers);
    if (!constants->forks)
        return (0);
    constants->data_locks = malloc(sizeof(pthread_mutex_t) * constants->num_philosophers);
    if (!constants->data_locks)
    {
        free(constants->forks);
        return (0);
    }
    i = 0;
    while (i < constants->num_philosophers)
    {
        pthread_mutex_init(&constants->forks[i], NULL);
        pthread_mutex_init(&constants->data_locks[i], NULL);
        i++;
    }
    pthread_mutex_init(&constants->print_lock, NULL);
    pthread_mutex_init(&constants->stop_lock, NULL);
    constants->simulation_stopped = 0;
    return (1);
}
