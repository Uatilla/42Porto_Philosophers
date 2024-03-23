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

bool    sim_stop(t_table *table)
{
    bool    check_death;

    check_death = false;
    pthread_mutex_lock(&table->sim_stop_checker);
    if (table->philo_died == true)
        check_death = true;
    pthread_mutex_unlock(&table->sim_stop_checker);
    return (check_death);
}