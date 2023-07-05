/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:05:31 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/05 21:05:32 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_main	main;

	if (!check_args(argc, argv, &main))
		return (0);
	create_philos(&main);
	if (!create_threads(&main))
		return (0);
	join_threads(&main);
	cancel_threads(&main);
	system("leaks -q philo");
	return (0);
}

int	create_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->args.n_of_philos)
	{
		if (pthread_create(&main->philo[i].thread, NULL, philo_actions,
				&main->philo[i]) != 0)
			return (0);
		usleep(60);
		i++;
	}
	check_state(main);
	return (1);
}

void	join_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->args.n_of_philos)
	{
		pthread_join(main->philo[i].thread, NULL);
		i++;
	}
}

void	cancel_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->args.n_of_philos)
	{
		pthread_detach(main->philo[i].thread);
		pthread_mutex_unlock(&main->philo[i].left_fork->mutex);
		pthread_mutex_destroy(&main->philo[i].left_fork->mutex);
		pthread_mutex_unlock(&main->philo[i].last_time_mutex);
		pthread_mutex_destroy(&main->philo[i].last_time_mutex);
		pthread_mutex_unlock(&main->philo[i].dead_lock);
		pthread_mutex_destroy(&main->philo[i].dead_lock);
		i++;
	}
	pthread_mutex_unlock(&main->args.dead_mutex);
	pthread_mutex_destroy(&main->args.dead_mutex);
	free(main->philo);
	free(main->fork);
}
