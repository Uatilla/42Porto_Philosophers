/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:20:51 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/13 20:20:53 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	doing_routine(t_table *table, t_philo *philo, long time)
{
	long long	i;
	bool		any_death;

	i = timestamp();
	while (timestamp() - i < time && !(stop_simulation(philo)))
	{
		pthread_mutex_lock(&table->sim_stop_checker);
		any_death = table->philo_died;
		pthread_mutex_unlock(&table->sim_stop_checker);
		if (any_death)
			break ;
		usleep(100);
	}
}

void	print_event(t_philo *philo, char *str, char *color)
{
	bool		any_death;

	pthread_mutex_lock(&philo->table->write_locker);
	any_death = philo->table->philo_died;
	if (any_death)
	{
		pthread_mutex_unlock(&philo->table->write_locker);
		return ;
	}
	printf("%s%ld ", color, timestamp() - philo->table->start_time);
	printf("%d ", philo->id);
	printf("%s\n" RESET, str);
	pthread_mutex_unlock(&philo->table->write_locker);
	return ;
}

bool	is_white_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long int	ft_atoi_positive(char *str)
{
	long int	num;

	num = 0;
	while (is_white_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - 48;
		str++;
	}
	return (num);
}
