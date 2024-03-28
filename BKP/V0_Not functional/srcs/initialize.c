/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:20:02 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/14 19:20:04 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t  *init_forks_mutexes(t_table *table)
{
    pthread_mutex_t *forks;
    unsigned int    i;

    forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
    if (!forks)
        return (handle_error_and_exit(ERR_MALLOC, FORK_INIT, 0));
    i = 0;
    /*Why these functions uses the var table as NULL?*/
    while (i < table->nbr_philos)
    {
        if (pthread_mutex_init (&forks[i], 0) != 0)
            return (handle_error_and_exit(ERR_MUTEX, FORK_INIT, 0));
        i++;
    }
    return (forks);
}

static void     assign_forks(t_philo    *philo)
{
    philo->fork[0] = philo->id;
    philo->fork[1] = (philo->id + 1) % philo->table->nbr_philos;
    if (philo->id % 2)
    {
        philo->fork[0] = (philo->id + 1) % philo->table->nbr_philos;
        philo->fork[1] = philo->id;
    }
}

static t_philo  **initialize_philos(t_table *table)
{
    t_philo     **philos;
    unsigned int    i;

    philos = malloc(sizeof(t_philo) * table->nbr_philos);
    if (!philos)
        return (handle_error_and_exit(ERR_MALLOC, PHILO_INIT, 0));
    i = 0;
    while (i < table->nbr_philos)
    {
        /*Considering that the **philos were allocated and each philosopher
        was allocated too, since a malloc error happens during the mutex
        initialization for example, should the var on handle_error_and_exit
        be zero? check with valgrind!*/
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return (handle_error_and_exit(ERR_MALLOC, PHILO_INIT, 0));
        if (pthread_mutex_init(&philos[i]->meal_time_locker, 0) != 0)
            return (handle_error_and_exit(ERR_MUTEX, NULL, 0));
        philos[i]->table = table;
        philos[i]->id = i;
        philos[i]->meal_count = 0;
        assign_forks(philos[i]);
        i++;
    }
    return (philos);
}

static bool init_global_mutexes(t_table *table)
{
    table->fork_locker = init_forks_mutexes(table);
    if (!table->fork_locker)
        return (false);
    if (pthread_mutex_init(&table->sim_stop_locker, 0) != 0)
        return (error_manage(ERR_MUTEX, "Simulation stopper.\n", table));
    if (pthread_mutex_init(&table->write_locker, 0) != 0)
        return (error_manage(ERR_MUTEX, "Write locker.\n", table));
    return (true);
}

t_table *initialize_table(int argc, char **argv, int i)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (handle_error_and_exit(ERR_MALLOC, TABLE_INIT, 0));
    table->nbr_philos = ft_atoi_positive(argv[i++]);
    table->time_to_die = ft_atoi_positive(argv[i++]);
    table->time_to_eat = ft_atoi_positive(argv[i++]);
    table->time_to_sleep = ft_atoi_positive(argv[i++]);
    if (argc == 6)
        table->max_meals = ft_atoi_positive(argv[i]);
    
    
    
    table->philos = initialize_philos(table);
    if (!table->philos)
        return (NULL);
    if (!init_global_mutexes(table))
        return (NULL);
    table->stop_simulation = false;
    return (table);
}