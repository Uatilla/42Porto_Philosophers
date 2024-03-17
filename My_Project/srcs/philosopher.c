/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:15:00 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/17 18:15:02 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philosopher(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->table->max_meals == 0)
        return (NULL);
    
    return (NULL);
}