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
# include <unistd.h>

// STRUCTURES
typedef enum e_status
{
    DIED = 0,
    EATING = 1,
    SLEEPING = 2,
    THINKING = 3,
    GOT_FORK_1 = 4,
    GOT_FORK_2 = 5
}   t_status;

typedef struct s_table  t_table;

typedef struct s_philo
{
    t_table         *table;
    unsigned int    id;
    unsigned int    meal_count;
    unsigned int    fork[2];
    time_t          last_meal_start; //Will be started when the pthread be called.
    pthread_t       philo_th;
    pthread_mutex_t set_meal_start;
}   t_philo;
typedef struct s_table
{
    unsigned int    nbr_philos;
    time_t          time_to_die;
    time_t          time_to_eat;
    time_t          time_to_sleep;
    int             max_meals;
    t_philo         **philos;
    time_t          start_time;
    bool            philo_died;
    pthread_mutex_t *fork_locker;
    pthread_mutex_t sim_stop_checker;
    pthread_mutex_t write_locker;
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
# define TABLE_INIT "Table wasn't initialized properly.\n"
# define PHILO_INIT "Philosopher wasn't initialized properly.\n"
# define ERR_MUTEX "ERROR: MUTEX COULDN'T BE INITIALIZED\n"
# define FORK_INIT "Fork wasn't initiliazed properly.\n"
# define ERR_THREAD "ERROR: THREAD COULDN'T BE INITIALIZED\n"

// FUNCTION PROTOTYPES
// input_validation.c
bool		validate_input(int argc, char **argv);

// exit.c
int			msg(char *str, char *detail, int exit_nbr);
void        *handle_error_and_exit(char *str, char *detail, t_table *table);
int         error_manage(char *str, char *detail, t_table *table);

// initialize.c
t_table     *initialize_table(int argc, char **argv, int i);

//time.c
time_t      timestamp(void);

//utils.c
bool		is_white_space(char c);
long int	ft_atoi_positive(char *str);

//philo_routine.c
void        *philo_routine(void *data);

//monitor.c
bool        sim_stop(t_table *table);

//output.c
void    print_event(t_philo *philo, char *str);
#endif
