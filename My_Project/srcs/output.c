/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:07:14 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/23 16:07:16 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_event(t_philo *philo, char *str)//I could modify every time I ask this function to call the table directly.
{
    pthread_mutex_lock(&philo->table->write_locker);
    if (!(philo->table->philo_died))
    {
        printf("%ld ", timestamp() - philo->table->start_time);
        printf("%d ", philo->id);
        printf("%s\n", str);
    }
    pthread_mutex_unlock(&philo->table->write_locker);
    return ;
}