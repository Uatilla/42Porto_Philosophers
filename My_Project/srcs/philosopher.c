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
    pthread_mutex_lock(&)
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
    philo->last_meal_time = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_locker);
    while (get_ms_time() < philo->table->start_time)
        continue ;
    if (philo->table->nbr_philos == 1)
        return(lone_philo_routine(philo));
    return (NULL);
}