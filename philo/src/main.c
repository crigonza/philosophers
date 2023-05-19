/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:05:31 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/19 14:31:54 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
    t_main  main;

    check_args(argc, argv, &main);
    create_philos(&main);
    create_threads(&main);
    system("leaks -q philo");
    return (0);
}

void create_threads(t_main *main)
{
    int i;

    i = 0;
    main->threads = malloc(sizeof(pthread_t) * main->args.n_of_philos);
    while (i < main->args.n_of_philos)
    {
        pthread_create(&main->threads[i], NULL, philo_states, &main->philo[i]);
        i++;
    }
}