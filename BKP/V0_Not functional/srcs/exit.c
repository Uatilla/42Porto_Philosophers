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

void	*free_table(t_table *table)
{
	unsigned int	i;
	if (!table)
		return (NULL);
	if (table->fork_locker != NULL)
		free(table->fork_locker);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

int	msg(char *str, char *detail, int exit_nbr)
{
	printf("%s", str);
	if (detail)
		printf("%s", detail);
	return (exit_nbr);
}

void	*handle_error_and_exit(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, detail, EXIT_FAILURE);
	return (NULL);
}

int		error_manage(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, detail, 0));
}