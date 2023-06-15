/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:26:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/15 12:58:31 by crigonza         ###   ########.fr       */
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
        main->philo[i].death = 0;
        main->philo[i].args = &main->args;
        main->philo[i].last = get_time();
        main->philo[i].thread = malloc(sizeof(pthread_t));
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
        usleep(5);
        now = get_time() - start;
    }
}

int pick_forks(t_philo *philo)
{
    if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
        return(0);
    print_actions(philo, 1);
    if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
        return(0);
    print_actions(philo, 1);
    return(1);
}

int philo_is_eating(t_philo *philo)
{
    if (!philo->death)
    {
        if (!pick_forks(philo))
            return(0);
        if (!check_death(philo))
            return(0);
        philo->last = get_time();
        print_actions(philo, 2);
        //usleep(philo->args->time_to_eat * 1000);
        take_time(philo->args->time_to_eat);
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
    }
    return(1);
}

void philo_is_sleeping(t_philo *philo)
{
    print_actions(philo, 3);
    take_time(philo->args->time_to_sleep);
    check_death(philo);
}