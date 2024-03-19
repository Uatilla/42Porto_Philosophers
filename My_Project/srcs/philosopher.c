/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:15:00 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/17 18:15:02 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *lone_philo_routine(t_philo *philo)
{
    /*
    1) TRY TO EAT:
        
    LOCK FORK

        Take the fork
            How to assign the fork to the philo?
            How to assure that this fork is not available for others?
            How to write on the screen that a fork was pick?
        Try to EAT since has only one fork, wait for another fork.
            How to assure that the philo will not eat since he doesn't have 
            two forks available.
    2) DIE:
    UNLOCK FORK
        How to assure that the philo will die since the die time was elapsed?
        How to return the feedback to the terminal that the philo died inside the time available
            (10 ms).
        Return
    */
    return (NULL);
}

void    *philosopher(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->table->time_to_die == 0)
        return (NULL);
    if (philo->table->max_meals == 0)
        return (NULL);
    pthread_mutex_lock(&philo->meal_time_locker);
    /*Considering that this variable below is not shared with all threads, 
    since the current var is inside the structure of the philo itself, it should
    use lock to write on it?*/
    philo->last_meal_time = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_locker);
    while (get_ms_time() < philo->table->start_time)
        continue ;
    if (philo->table->nbr_philos == 1)
        return(lone_philo_routine(philo));
    return (NULL);
}