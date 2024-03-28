/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:56:48 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/23 14:56:52 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	stop_simulation(t_philo *philo)
{
	bool	philo_full;
	bool	death;

	pthread_mutex_lock(&philo->table->sim_stop_checker);
	death = philo->table->philo_died;
	pthread_mutex_unlock(&philo->table->sim_stop_checker);
	if (death)
		return (true);
	pthread_mutex_lock(&philo->meal_death_checker);
	philo_full = philo->full;
	pthread_mutex_unlock(&philo->meal_death_checker);
	if (philo_full)
		return (true);
	return (false);
}

static bool	death_checker(t_table *table, t_philo **philo)
{
	unsigned int	i;
	bool		philo_full;
	long		time_hungry;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&philo[i]->last_meal_locker);
		pthread_mutex_lock(&philo[i]->meal_death_checker);
		philo_full = philo[i]->full;
		time_hungry = timestamp() - philo[i]->last_meal_start;
		pthread_mutex_unlock(&philo[i]->last_meal_locker);
		pthread_mutex_unlock(&philo[i]->meal_death_checker);
		if (!philo_full && time_hungry >= table->time_to_die)
		{
			pthread_mutex_lock(&table->sim_stop_checker);
			table->philo_died = true;
			pthread_mutex_unlock(&table->sim_stop_checker);
			print_event(philo[i], "died");
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	meal_done_checker(t_table *table, t_philo **philo)
{
	unsigned int	i;
	bool			philo_full;

	if (table->max_meals == -1)
		return (false);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&philo[i]->meal_death_checker);
		philo_full = philo[i]->full;
		pthread_mutex_unlock(&philo[i]->meal_death_checker);
		if (!philo_full)
			return (false);
		i++;
	}
	if (i == table->nbr_philos)
	{
		pthread_mutex_lock(&table->sim_stop_checker);
		table->all_full = true;
		pthread_mutex_unlock(&table->sim_stop_checker);
		return (true);
	}
	return (false);
}

void	*sim_stop_checker(void *data)
{
	t_table	*table;
	bool	any_death;
	t_philo **philo;
	int i;

	i = 0;

	table = (t_table *)data;
	philo = table->philos;
	pthread_mutex_lock(&table->sim_stop_checker);
	any_death = table->philo_died;
	pthread_mutex_unlock(&table->sim_stop_checker);
	if (any_death)
		return (NULL);
	while (!(meal_done_checker(table, philo)))
	{
		i++;
		if (death_checker(table, philo))
			return (NULL);

		usleep(500);
	}
	return (NULL);
}
