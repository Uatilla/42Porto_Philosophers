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

/*ADD THE CONDITION FOR WHITE SPACES AND '+'*/
long int ft_atoi_positive(char *str)
{
    long int num;

    num = 0;
    while (*str >= '0' && *str <= '9')
    {
        num *= 10;
        num += *str - 48;
        str++;
    }
    return (num);

}

static bool     check_int_max(char *str)
{
    if (ft_atoi_positive(str) > INT_MAX)
        return (false);
    return (true);
}

/*ADD THE CONDITION FOR WHITE SPACES AND '+' SIGN;*/
static bool     is_it_positiv_numeric(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

bool    validate_input(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
        return (msg(INPUT_ERROR, HOW_TO_INPUT, EXIT_FAILURE));
    i = 0;
    while (++i < argc)
    {
        if(!is_it_positiv_numeric(argv[i]))
            return (msg(INPUT_ERROR, VALUES, EXIT_FAILURE));
        if(!check_int_max(argv[i]))
            return (msg(INPUT_ERROR, OUT_RANGE, EXIT_FAILURE));
    }
    return (EXIT_SUCCESS);
}