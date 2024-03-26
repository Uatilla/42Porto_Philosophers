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

bool    sim_stop(t_philo *philo)
{
    pthread_mutex_lock(&philo->set_meal_start);
    if (philo->full == true)
        return (true);
    pthread_mutex_unlock(&philo->set_meal_start);
    return (false);
}