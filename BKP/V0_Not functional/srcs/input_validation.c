/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:29:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/11 20:29:29 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_int_max(char *str)
{
	if (ft_atoi_positive(str) > INT_MAX)
		return (false);
	return (true);
}

static bool	is_it_positiv_numeric(char *str)
{
	if (*str == '\0')
		return (false);
	while (is_white_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str && *str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

bool	validate_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (msg(INPUT_ERROR, HOW_TO_INPUT, false));
	i = 0;
	while (++i < argc)
	{
		if (!is_it_positiv_numeric(argv[i]))
			return (msg(INPUT_ERROR, VALUES, false));
		if (!check_int_max(argv[i]))
			return (msg(INPUT_ERROR, OUT_RANGE, false));
		if (i == 1 && ft_atoi_positive(argv[i]) == 0)
			return (msg(INPUT_ERROR, NO_PHILO, false));
	}
	return (true);
}
