/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:31:48 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/29 12:11:09 by crigonza         ###   ########.fr       */
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
	unsigned int	start;
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

typedef enum e_state
{
	TAKEFORK,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}					t_state;

typedef struct s_philo
{
	t_state			state;
	int				id;
	long int		last_time;
	int				meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_args			*args;
	pthread_t		thread;
	pthread_mutex_t	action_mutex;
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
int					pick_forks(t_philo *philo);
int					philo_is_eating(t_philo *philo);
void				philo_is_sleeping(t_philo *philo);
void				philo_is_thinking(t_philo *philo);
//--------------------main.c------------------------//
int					main(int argc, char **argv);
int					create_threads(t_main *main);
void				join_threads(t_main *main);
int					watcher(t_philo *philo);
void				cancel_threads(t_main *main);
//--------------------states.c----------------------//
int					check_death(t_philo *philo);
void				check_meals(t_philo *philo);
void				*philo_actions(void *args);
void				*check_state(void *args);
//--------------------utils.c-----------------------//
int					ph_atoi(const char *nptr);
void				print_actions(t_philo *philo);
long int			get_time(void);
void				take_time(long int time);

#endif