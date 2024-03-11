/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:09:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/11 20:09:52 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// MACROS
#define INPUT_ERROR "ERROR: INVALID INPUT\n"
#define HOW_TO_INPUT "How to use: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
#define VALUES "Only positive numbers are allowed.\n"

// FUNCTION PROTOTYPES
// input_validation.c
bool    validate_input(int argc, char **argv);
int     msg(char *str, char *detail, int exit_nbr);
#endif