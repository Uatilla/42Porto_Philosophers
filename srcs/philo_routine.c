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
	print_event(philo, "is thinking", GREEN);
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
}

static void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sim_stop_checker);
	print_event(philo, "is sleeping", DARK_GRAY);
	if (philo->table->all_full)
	{
		pthread_mutex_unlock(&philo->table->sim_stop_checker);
		return ;
	}
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
	doing_routine(philo->table, philo, philo->table->time_to_sleep);
	usleep(100);
}

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
	print_event(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[1]]);
	print_event(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(&philo->last_meal_locker);
	philo->last_meal_start = timestamp();
	print_event(philo, "is eating", BLUE);
	pthread_mutex_unlock(&philo->last_meal_locker);
	doing_routine(philo->table, philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[1]]);
	pthread_mutex_lock(&philo->meal_death_checker);
	philo->meal_count++;
	if ((int) philo->meal_count == philo->table->max_meals)
		philo->full = true;
	pthread_mutex_unlock(&philo->meal_death_checker);
}

void	print_event2(t_philo *philo, char *str, char*color)
{
	(void)color;
	bool		any_death;

	pthread_mutex_lock(&philo->table->write_locker);
	any_death = philo->table->philo_died;
	if (any_death)
	{
		pthread_mutex_unlock(&philo->table->write_locker);
		return ;
	}
	printf("%s%ld "  RESET, color, timestamp() - philo->table->start_time);
	printf("%d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->table->write_locker);
	return ;
}

void	*lone_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locker[philo->fork[0]]);
	print_event(philo, "has taken a fork", YELLOW);
	pthread_mutex_unlock(&philo->table->fork_locker[philo->fork[0]]);
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->max_meals == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->last_meal_locker);
	philo->last_meal_start = philo->table->start_time;
	pthread_mutex_unlock(&philo->last_meal_locker);
	wait_start(philo);
	if (philo->table->nbr_philos == 1)
		return (lone_philo(philo));
	else if (philo->id % 2 == true)
		usleep(500);
	while (!stop_simulation(philo))
	{
		eat_routine(philo);
		if (!stop_simulation(philo))
			sleep_routine(philo);
		if (!stop_simulation(philo))
			think_routine(philo);
	}
	return (NULL);
}
