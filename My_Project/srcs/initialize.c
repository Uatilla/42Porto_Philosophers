/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:20:02 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/14 19:20:04 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *initialize_table(int argc, char **argv, int i)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (handle_error_and_exit(ERR_MALLOC, TABLE_INIT, 0));
    table->nbr_philos = ft_atoi_positive(argv[i++]);
    table->time_to_die = ft_atoi_positive(argv[i++]);
    table->time_to_eat = ft_atoi_positive(argv[i++]);
    table->time_to_sleep = ft_atoi_positive(argv[i++]);
    if (argc == 6)
        table->max_meals = ft_atoi_positive(argv[i]);
    return (table);
}