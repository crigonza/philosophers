/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:31:48 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/19 14:26:29 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_H
#define  PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct s_args
{
    int n_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_filosopher_must_eat;
}   t_args;

typedef struct s_fork {
    int id;
}t_fork;

typedef struct s_philo 
{
    enum
    {
        THINKING,
        SLEEPING,
        EATING
    }e_state;
    int id;
    t_fork  *left_fork;
    t_fork  *right_fork;
} t_philo;

typedef struct s_main
{
    t_args  args;
    t_philo  *philo;
    t_fork  *fork;
    pthread_t *threads;
} t_main;

//------------------check_args.c--------------------//
void            check_args(int argc, char **argv, t_main *main);
void            args_error(void);
//-------------------philos.c-----------------------//
void            create_philos(t_main *main);
//--------------------main.c------------------------//
int             main(int argc, char **argv);
void            create_threads(t_main *main);
//--------------------states.c----------------------//
void            philo_states(t_main *main);
//--------------------utils.c-----------------------//
int             ph_atoi(const char *nptr);











#endif