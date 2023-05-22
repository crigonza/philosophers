/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:26:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/19 13:50:38 by crigonza         ###   ########.fr       */
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
        if (i != 0)
            main->philo[i].left_fork = &main->fork[i - 1];
        main->philo[i].right_fork = &main->fork[i];
        i++;
    }
    i--;
    main->philo[0].left_fork = &main->fork[i];

    while(i >= 0)
    {
        printf("filosofo id: %d  ", main->philo[i].id);
        printf("tenedor izq: %d  ", main->philo[i].left_fork->id);
        printf("tenedor drch: %d\n", main->philo[i].right_fork->id);
        i--;
    }
}