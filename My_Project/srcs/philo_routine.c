/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:47:02 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/20 16:47:07 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void doing_routine(t_table *table)
{
    long long i;

    i = timestamp();
    while (!(table->philo_died))
    {
        if ((i - timestamp()) >= table->time_to_eat)
            break ;
        usleep(10);
    }
}

static void eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
    print_event(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[1]]);
    print_event(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->set_meal_start);
    philo->last_meal_start = timestamp();
    pthread_mutex_unlock(&philo->set_meal_start);
    doing_routine(philo->table);
    //pause o philo por time_to_eat.
    //Como verificar a morte do philo durante a refeicao
    pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
    pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[1]]);

}

void    *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->table->max_meals == 0)
        return (NULL);
    if (philo->table->time_to_die == 0)
        return (NULL);
    pthread_mutex_lock(&philo->set_meal_start);
    philo->last_meal_start = philo->table->start_time;
    pthread_mutex_unlock(&philo->set_meal_start);
    while (timestamp() < philo->table->start_time)
        continue ;
    if (philo->table->nbr_philos == 1)
        printf("Lone Philo Function call\n");
    /*else if (philo->id % 2 == true)
        printf("think_routine(philo)\n");*/
    while (!sim_stop(philo->table))
    {
        eat_routine(philo);
    }
    return (NULL);
}