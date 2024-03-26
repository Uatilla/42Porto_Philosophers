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

static pthread_mutex_t *init_fork_mutexes(t_table *table)
{
    pthread_mutex_t *fork;
    unsigned int    i;

    fork = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
    if (!fork)
        return (handle_error_and_exit(ERR_MUTEX, "", table));
    i = 0;
    while (i < table->nbr_philos)
    {
        if(pthread_mutex_init(&fork[i], NULL) != 0)
            return (handle_error_and_exit(ERR_MUTEX, "", table));
        i++;
    }
    return (fork);
}

static bool init_mutexes(t_table *table)
{
    table->fork_locker = init_fork_mutexes(table);
    if (!(table->fork_locker))
        return (false);
    if (pthread_mutex_init(&table->sim_stop_checker, NULL) != 0)
        return (false);
    if (pthread_mutex_init(&table->write_locker, NULL) != 0)
        return (false);
    return (true);
}

static void assign_fork(t_philo *philo)
{
    philo->fork[0] = philo->id;
    philo->fork[1] = (philo->id + 1) % philo->table->nbr_philos;
    if (philo->id % 2)
    {
        philo->fork[0] = (philo->id + 1) % philo->table->nbr_philos;
        philo->fork[1] = philo->id;
    }
    printf("Philo: %d F1: %d F2: %d\n", philo->id, philo->fork[0], philo->fork[1]);
}

static t_philo **initialize_philo(t_table *table)
{
    t_philo **philos;
    unsigned int    i;

    /*ALL RETURN ERROR MUST CHANGE SINCE THE PHILO STRUCTURE ARE NOT
    NULL ANYMORE, (OF COURSE AFTER THE ALOCATION OF THE FIRST ONE)
    The function free_table need to be able to deal with the philo 
    structure.*/
    philos = malloc(sizeof(t_philo) * table->nbr_philos);
    if (!philos)
        return (handle_error_and_exit(ERR_MALLOC, PHILO_INIT, 0));
    i = 0;
    while(i < table->nbr_philos)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return(handle_error_and_exit(ERR_MALLOC, PHILO_INIT, 0));
        philos[i]->id = i;
        philos[i]->table = table;
        philos[i]->meal_count = 0;
        philos[i]->full = false;
        assign_fork(philos[i]);
        if (pthread_mutex_init(&philos[i]->set_meal_start, NULL) != 0)
            return (NULL);
        i++;
    }

    return (philos);
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
    else
        table->max_meals = -1;
    if (!init_mutexes(table))
        return (handle_error_and_exit(ERR_MUTEX, "", table));
    table->philos = initialize_philo(table);
    if (!table->philos)
        return (handle_error_and_exit(ERR_MALLOC, PHILO_INIT, table));
    return (table);
}