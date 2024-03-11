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

int     is_it_numeric(char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (EXIT_FAILURE);
        str++;
    }
    return (EXIT_SUCCESS);
}

bool    validate_input(int argc, char **argv)
{
    int i;

    printf("Argc: %d, Argv[1]:%s\n", argc, argv[1]);
    if (argc < 5 || argc > 6)
        return (msg(INPUT_ERROR, HOW_TO_INPUT, EXIT_FAILURE));
    i = 0;
    while (++i < argc)
    {
        if(!is_it_numeric(argv[i]))
            return (msg(INPUT_ERROR, VALUES, EXIT_FAILURE));
        //ATTRIBUTES THE NUMBER VALUE INT0 A VARIABLE
        //VALIDATE THAT THE NUMBER IS BELOW INT MAX AND ZERO.
    }
    return (EXIT_SUCCESS);
}