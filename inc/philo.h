/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:31:48 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/05 21:17:57 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				is_dead;
	long int		start;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				must_eat_count;
	pthread_mutex_t	dead_mutex;
}					t_args;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	long int		last_time;
	pthread_mutex_t	last_time_mutex;
	int				meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_args			*args;
	pthread_t		thread;
	pthread_mutex_t	dead_lock;
}					t_philo;

typedef struct s_main
{
	t_args			args;
	t_philo			*philo;
	t_fork			*fork;
}					t_main;

//------------------check_args.c--------------------//
int					check_args(int argc, char **argv, t_main *main);
int					valid_args(int argc, char **argv);
int					get_args(int argc, char **argv, t_main *main);
//-------------------philos.c-----------------------//
void				create_philos(t_main *main);
//--------------------main.c------------------------//
int					main(int argc, char **argv);
int					create_threads(t_main *main);
void				join_threads(t_main *main);
void				cancel_threads(t_main *main);
//--------------------states.c----------------------//
void				check_meals(t_philo *philo);
void				*philo_actions(void *args);
void				*check_state(t_main *main);
void				philo_routine(t_philo *philo);
//--------------------utils.c-----------------------//
int					ph_atoi(const char *nptr);
void				print_actions(t_philo *philo, char *state);
long int			get_time(void);
void				take_time(long int time);

#endif