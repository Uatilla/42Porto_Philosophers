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

static void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sim_stop_checker);
	if (philo->table->all_full)
	{
		pthread_mutex_unlock(&philo->table->sim_stop_checker);
		return ;
	}
	print_event(philo, "is thinking");
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
}

static void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sim_stop_checker);
	print_event(philo, "is sleeping");
	if (philo->table->all_full)
	{
		pthread_mutex_unlock(&philo->table->sim_stop_checker);
		return ;
	}
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
	doing_routine(philo->table, philo->table->time_to_sleep);
	usleep(50);
}

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
	print_event(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[1]]);
	print_event(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->sim_stop_checker);
	philo->last_meal_start = timestamp();
	print_event(philo, "is eating");
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
	doing_routine(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[1]]);
	pthread_mutex_lock(&philo->set_meal_start);
	philo->meal_count++;
	if ((int) philo->meal_count == philo->table->max_meals)
		philo->full = true;
	pthread_mutex_unlock(&philo->set_meal_start);
}

void	lone_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
	printf("%ld 0 has taken a fork\n", timestamp() - philo->table->start_time);
    //print_event(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

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
    {
		lone_philo(philo);
        return (NULL);
    }
	else if (philo->id % 2 == true)
		usleep(500);
	while (!(philo->table->philo_died) && !(philo->table->all_full))
	{
		eat_routine(philo);
		if (!(philo->table->philo_died))
			sleep_routine(philo);
		if (!(philo->table->philo_died))
			think_routine(philo);
	}
	return (NULL);
}
