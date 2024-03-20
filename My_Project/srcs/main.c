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

static bool start_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if(pthread_create(&table->philos[i]->philo_th, \
			NULL, &philo_routine, table->philos[i]) != 0)
                return (false); //This return should deal with errors.
		i++;
	}
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i]->philo_th, NULL) != 0)
			return (false); //This return should deal with errors.
		i++;
	}
	printf("OLA: %d\n", table->philos[0]->fork[0]);
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
	/*Start the program*/
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	printf("Nbr Philos: %d\n", table->nbr_philos);
	printf("Time to Die: %d\n", (int)table->time_to_die);
	printf("Time to eat: %d\n", (int)table->time_to_eat);
	printf("Time to Sleep: %d\n", (int)table->time_to_sleep);
	if (table->max_meals)
		printf("Max meals: %d\n", table->max_meals);
	return (EXIT_SUCCESS);
}
