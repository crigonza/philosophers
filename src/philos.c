/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:26:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/18 19:41:56 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void create_philos(t_main *main)
{
    int     i;

    i = 0;
    main->philo = malloc(sizeof(t_philo) * main->args.n_of_philos);
    main->fork = malloc(sizeof(t_fork) * main->args.n_of_philos);
    while (i < main->args.n_of_philos)
    {
        main->fork[i].id = i + 1;
        main->philo[i].id = i + 1;
        main->philo[i].meals = 0;
        main->philo[i].args = &main->args;
        main->philo[i].last_time = get_time();
        //main->philo[i].thread = malloc(sizeof(pthread_t));
        if (i != 0)
            main->philo[i].left_fork = &main->fork[i - 1];
        main->philo[i].right_fork = &main->fork[i];
        pthread_mutex_init(&main->fork[i].mutex, NULL);
        i++;
    }
    i--;
    main->philo[0].left_fork = &main->fork[i];

    /* while(i >= 0)
    {
        printf("filosofo id: %d  ", main->philo[i].id);
        printf("tenedor izq: %d  ", main->philo[i].left_fork->id);
        printf("tenedor drch: %d\n", main->philo[i].right_fork->id);
        i--;
    } */
}

void take_time(int time)
{
    int  start;
    int  now;

    now = 0;
    start = (int)get_time();
    while(time != now)
    {
        usleep(10);
        now = get_time() - start;
    }
}

int pick_forks(t_philo *philo)
{
    if(!philo->args->is_dead)
    {
        if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
            return(0);
        philo->state = TAKEFORK;
        print_actions(philo);
        if(!philo->args->is_dead)
        {
            if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
                return(0);
            philo->state = TAKEFORK;
            print_actions(philo);
        }
    }
    else
        return(0);
    return(1);
}

void check_meals(t_philo *philo)
{
    if (philo->meals < philo->args->times_must_eat)
        philo->meals ++;
    if (philo->meals == philo->args->times_must_eat)
    {
        if(philo->args->must_eat_count != 0)
            philo->args->must_eat_count--;
    }
    /* printf("*******philo %d meals: %d*******\n", philo->id, philo->meals);
    printf("*******all ate: %d*******\n", philo->args->must_eat_count); */
}

int philo_is_eating(t_philo *philo)
{
    if (!philo->args->is_dead)
    {
        if (!pick_forks(philo))
            return(0);
        if (philo->args->is_dead)
            return(0);
        philo->last_time = get_time();
        philo->state = EATING;
        print_actions(philo);
        if(philo->args->times_must_eat != -1)
            check_meals(philo);
        take_time(philo->args->time_to_eat);
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
    }
    return(1);
}

void philo_is_sleeping(t_philo *philo)
{
    if (!philo->args->is_dead)
    {
        philo->state = SLEEPING;
        print_actions(philo);
        take_time(philo->args->time_to_sleep);
    }
}