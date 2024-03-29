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

static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = get_ms_time() + (table->nbr_philos * 2 * 10);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i]->philo_thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (error_manage(ERR_THREAD, "Philosopher Thread.\n",
									table));
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (!validate_input(argc, argv))
		return (EXIT_FAILURE);
	table = initialize_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if(!start_simulation(table))
		return (EXIT_FAILURE);

	printf("Nbr Philos: %d\n", table->nbr_philos);
	printf("Time to Die: %d\n", (int)table->time_to_die);
	printf("Time to eat: %d\n", (int)table->time_to_eat);
	printf("Time to Sleep: %d\n", (int)table->time_to_sleep);
	if (table->max_meals)
		printf("Max meals: %d\n", table->max_meals);
	return (EXIT_SUCCESS);
}
