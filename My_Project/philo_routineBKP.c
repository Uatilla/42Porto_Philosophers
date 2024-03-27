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

static void doing_routine(t_table *table, time_t time)
{
    long long i;

    i = timestamp();
    while (!(table->philo_died))
    {
        if ((timestamp() - i) >= time)
            break ;
        usleep(10);
    }
}

static void think_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->sim_stop_checker);
    print_event(philo, "is thinking");
    pthread_mutex_unlock(&philo->table->sim_stop_checker);
}

static void sleep_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->sim_stop_checker);
    print_event(philo, "is sleeping");
    pthread_mutex_unlock(&philo->table->sim_stop_checker);
    doing_routine(philo->table, philo->table->time_to_sleep);
    //How to add this sleep in a proper way.
    usleep(50);
}

static void eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
    print_event(philo, "has taken a fork");
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[1]]);
    print_event(philo, "has taken a fork");
    pthread_mutex_lock(&philo->set_meal_start);
    philo->last_meal_start = timestamp();
    pthread_mutex_unlock(&philo->set_meal_start);
    pthread_mutex_lock(&philo->table->sim_stop_checker);
    print_event(philo, "is eating");
    pthread_mutex_unlock(&philo->table->sim_stop_checker);
    doing_routine(philo->table, philo->table->time_to_eat);
    pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
    pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[1]]);
    pthread_mutex_lock(&philo->set_meal_start);
    philo->meal_count++;
    if (philo->meal_count == philo->table->max_meals)
        philo->full = true;
    pthread_mutex_unlock(&philo->set_meal_start);
}

void    *lone_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
    print_event(philo, "has taken a fork");
    pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
    while ((timestamp() - philo->table->start_time) < philo->table->time_to_die)
        continue ;
    print_event(philo, "died");
    return (NULL);
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
    /*6) SPECIAL CASE
    How to deal with a lone philo.*/
    if (philo->table->nbr_philos == 1)
    {
        lone_philo(philo);
        return (NULL);
    }
    /*4) SYNC
    Why do I need this condition, should I ask the even philos to think?
    
    else if (philo->id % 2 == true)
    {
        print_event(philo, "is thinking\n");
        usleep(100);
    }
    */

    
    while (!sim_stop(philo))
    {
        eat_routine(philo);

        /* 2) MAXIMUM ATE
        On the visualizer the last meal is larger than it should be, and the condition for a
        a philo that already ate enough should change since, after ate enough it should
        stop the thread. */

        //if (!sim_stop(philo))
        sleep_routine(philo);
        if (!sim_stop(philo))
            think_routine(philo);
        
        //printf("ID: %d, FULL: %d\n", philo->id, philo->full);
    }
    return (NULL);
}