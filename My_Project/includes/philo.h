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

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

// STRUCTURES
typedef struct s_table  t_table;

typedef struct s_philo  
{
    pthread_mutex_t meal_time_locker;
    unsigned int    id;
    unsigned int    meal_count;
    t_table         *table;
    unsigned int    fork[2];
}   t_philo;

typedef struct s_table
{
    unsigned int    nbr_philos;
    time_t          time_to_die;
    time_t          time_to_eat;
    time_t          time_to_sleep;
    int             max_meals;
    t_philo         **philos;
}   t_table;


// MACROS

//Error messages:
# define INPUT_ERROR "ERROR: INVALID INPUT\n"
# define HOW_TO_INPUT "How to use: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define VALUES "Only positive numbers are allowed.\n"
# define OUT_RANGE "The input exceeds the maximum INT value: \
2147483647.\n"
# define NO_PHILO "The number of philosophers can't be zero.\n"
# define ERR_MALLOC "ERROR: MEMORY COULDN'T BE ALLOCATED\n"
# define TABLE_INIT "Table structure wasn't initialized properly.\n"
# define PHILO_INIT "Philosopher structure wasn't initialized properly.\n"
# define ERR_MUTEX "ERROR: MUTEX COULDN'T BE INITIALIZED\n"

// FUNCTION PROTOTYPES
// input_validation.c
bool		validate_input(int argc, char **argv);

// exit.c
int			msg(char *str, char *detail, int exit_nbr);
void        *handle_error_and_exit(char *str, char *detail, t_table *table);

// initialize.c
t_table     *initialize_table(int argc, char **argv, int i);

//utils.c
bool		is_white_space(char c);
long int	ft_atoi_positive(char *str);
#endif
