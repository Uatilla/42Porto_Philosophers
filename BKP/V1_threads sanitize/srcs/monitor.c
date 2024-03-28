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

static bool	meal_done_checker(t_table *table, t_philo **philo)
{
	unsigned int	i;

	if (table->max_meals != -1)
	{
		i = 0;
		while (i < table->nbr_philos && philo[i]->full == true)
			i++;
		if (i == table->nbr_philos)
			return (true);
	}
	return (false);
}

void	sim_stop_checker(t_table *table, t_philo **philo)
{
	unsigned int	i;

	while (timestamp() < table->start_time)
		continue ;
	while (!table->all_full)
	{
		i = -1;
		while (++i < table->nbr_philos && !(table->philo_died))
		{
			pthread_mutex_lock(&table->sim_stop_checker);
			if (timestamp() - philo[i]->last_meal_start > table->time_to_die)
			{
				print_event(philo[i], "died");
				table->philo_died = true;
			}
			pthread_mutex_unlock(&table->sim_stop_checker);
			usleep(100);
		}
		if (table->philo_died)
			break ;
		table->all_full = meal_done_checker(table, philo);
	}
}
