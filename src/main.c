/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:05:31 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/18 19:38:08 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
    t_main  main;

    check_args(argc, argv, &main);
    create_philos(&main);
    if(!create_threads(&main))
        return(0);
    if(!watcher(main.philo))
        return(0);
    join_threads(&main);
    cancel_threads(&main);
    system("leaks -q philo");
    return (0);
}

int create_threads(t_main *main)
{
    int i;

    i = 0;
    while (i < main->args.n_of_philos)
    {
        pthread_create(&main->philo[i].thread, NULL, philo_actions, &main->philo[i]);
        usleep(50);
        i++;
    }
    return(1);
}

void    join_threads(t_main *main)
{
    int i;

    i = 0;
    while (i < main->args.n_of_philos)
    {
        pthread_join(main->philo[i].thread, NULL);
        i++;
    }
}

int   watcher(t_philo *philo)
{
    pthread_t   watcher;

    pthread_create(&watcher, NULL, check_state, philo);
    pthread_join(watcher, NULL);
    pthread_detach(watcher);
    return(1);
}

void    cancel_threads(t_main *main)
{
    int i;

    i = 0;
    while(i < main->args.n_of_philos)
    {
        pthread_detach(main->philo[i].thread);
        pthread_mutex_unlock(&main->philo[i].left_fork->mutex);
        pthread_mutex_destroy(&main->philo[i].left_fork->mutex);
        i++;
    }
}

