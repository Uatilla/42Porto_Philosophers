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

static bool philo_ate_enough(t_philo *philo)
{
    /*Should have a fork before check this data?*/
    if (philo->meal_count == philo->table->max_meals)
        return (true);
    return (false);
}

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

static void eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
    print_event(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->table->fork_locker[philo->fork[1]]);
    print_event(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->set_meal_start);
    philo->last_meal_start = timestamp();
    pthread_mutex_unlock(&philo->set_meal_start);
    pthread_mutex_lock(&philo->table->sim_stop_checker);
    print_event(philo, "is eating\n");
    pthread_mutex_unlock(&philo->table->sim_stop_checker);
    doing_routine(philo->table, philo->table->time_to_eat);
    pthread_mutex_lock(&philo->set_meal_start);
    philo->meal_count++;
    pthread_mutex_unlock(&philo->set_meal_start);
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





    //Why do I need this condition, should I ask the even philos to think?






    /*else if (philo->id % 2 == true)
        printf("think_routine(philo)\n");*/
    while (!sim_stop(philo->table)) //This code can be simpler.
    {
        eat_routine(philo);
        if (philo_ate_enough(philo))//On the visualizer the last meal is larger than it should be.
            break;
        print_event(philo, "is sleeping\n");
        doing_routine(philo->table, philo->table->time_to_sleep);
        usleep(50);
        print_event(philo, "is thinking\n");
        //HOW TO COMUNICATE A PHILO DEATH

    }
    return (NULL);
}