/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:58:24 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/11 20:58:27 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleaning_philos(t_philo **philo, t_table *table)
{
	unsigned int	i;

	i = 0;
	while (philo[i] && i < table->nbr_philos)
	{
		pthread_mutex_destroy(&(table->fork_locker[i]));
		pthread_mutex_destroy(&(table->philos[i]->last_meal_locker));
		pthread_mutex_destroy(&(table->philos[i]->meal_death_checker));
		free(philo[i]);
		i++;
	}

	free(table->fork_locker);
	free(philo);
}

void	deallocate_destroy(t_table *table)
{
	if (table->philos)
	{
		cleaning_philos(table->philos, table);
		pthread_mutex_destroy(&(table->write_locker));
		pthread_mutex_destroy(&(table->sim_stop_checker));
	}
	if (table)
		free(table);
}

int	msg(char *str, char *detail, int exit_nbr)
{
	printf("%s", str);
	if (detail)
		printf("%s", detail);
	return (exit_nbr);
}

void	*clean_return(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		deallocate_destroy(table);
	msg(str, detail, EXIT_FAILURE);
	return (NULL);
}

int	error_manage(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		deallocate_destroy(table);
	return (msg(str, detail, 0));
}
