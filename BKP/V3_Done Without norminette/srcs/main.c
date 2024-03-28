/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:08 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/10 18:55:11 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	exit_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i]->philo_th, NULL) != 0)
			return (error_manage(ERR_THREAD, "Join Philo\n", table));
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
			return (error_manage(ERR_THREAD, "Join Monitor\n", table));
	deallocate_destroy(table);
	return (true);
}

static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = timestamp() + (table->nbr_philos * 2 * 10);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i]->philo_th, \
			NULL, &philo_routine, table->philos[i]) != 0)
			return (error_manage(ERR_THREAD, "Create Philo\n", table));
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &sim_stop_checker, \
			table) != 0)
		return (error_manage(ERR_THREAD, "Create Monitor\n", table));
	//sim_stop_checker(table, table->philos);
	
	
	return (exit_simulation(table));
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!validate_input(argc, argv))
		return (EXIT_FAILURE);
	table = initialize_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
