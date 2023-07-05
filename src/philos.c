/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:26:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/05 19:58:10 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_philos(t_main *main)
{
	int	i;

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
		pthread_mutex_init(&main->philo[i].last_time_mutex, NULL);
		pthread_mutex_init(&main->philo[i].dead_lock, NULL);
		if (i != 0)
			main->philo[i].left_fork = &main->fork[i - 1];
		main->philo[i].right_fork = &main->fork[i];
		pthread_mutex_init(&main->fork[i].mutex, NULL);
		i++;
	}
	i--;
	main->philo[0].left_fork = &main->fork[i];
}
