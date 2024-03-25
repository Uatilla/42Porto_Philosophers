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

	table->start_time = timestamp() + (table->nbr_philos * 2 * 10);
	i = 0;
	while (i < table->nbr_philos)
	{
		if(pthread_create(&table->philos[i]->philo_th, \
			NULL, &philo_routine, table->philos[i]) != 0)
            return (false); //This return should deal with errors.
		i++;
	}

	//Before the join I must run the death checker.
	//How the code here between create and join works?
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i]->philo_th, NULL) != 0)
			return (false); //This return should deal with errors.
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
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
