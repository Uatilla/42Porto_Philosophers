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
# include <string.h>

// STRUCTURES
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_mutex_t	last_meal_locker;
	pthread_mutex_t	meal_death_checker;
	unsigned int	id;
	unsigned int	meal_count;
	unsigned int	fork[2];
	long			last_meal_start;
	bool			full;
	bool			dead;
	t_table			*table;
	pthread_t		philo_th;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*fork_locker;
	pthread_mutex_t	sim_stop_checker;
	pthread_mutex_t	write_locker;
	pthread_t		monitor;
	unsigned int	nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	bool			philo_died;
	bool			all_full;
	t_philo			**philos;
	long			start_time;
}	t_table;

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
# define ERR_MUTEX "ERROR: MUTEX\n"
# define FORK_INIT "Fork wasn't initiliazed properly.\n"
# define ERR_THREAD "ERROR: THREAD\n"

// FUNCTION PROTOTYPES
// input_validation.c
bool		validate_input(int argc, char **argv);

// exit.c
void		*clean_return(char *str, char *detail, t_table *table);
void		deallocate_destroy(t_table *table);
int			msg(char *str, char *detail, int exit_nbr);
int			error_manage(char *str, char *detail, t_table *table);

// initialize.c
t_table		*initialize_table(int argc, char **argv, int i);

//utils.c
bool		is_white_space(char c);
long int	ft_atoi_positive(char *str);
long		timestamp(void);
void		print_event(t_philo *philo, char *str);
void		doing_routine(t_table *table, t_philo *philo, long time);

//philo_routine.c
void		*philo_routine(void *data);

//monitor.c
void		*sim_stop_checker(void *data);
bool		stop_simulation(t_philo *philo);
void		wait_start(t_philo *philo);

#endif
