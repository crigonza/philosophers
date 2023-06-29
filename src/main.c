/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:05:31 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/29 13:02:19 by crigonza         ###   ########.fr       */
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
	if (!watcher(main.philo))
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
		usleep(10);
		i++;
	}
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

int	watcher(t_philo *philo)
{
	pthread_t	watcher;

	if (pthread_create(&watcher, NULL, check_state, philo) != 0)
		return (0);
	pthread_join(watcher, NULL);
	pthread_detach(watcher);
	return (1);
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
		pthread_mutex_unlock(&main->philo[i].action_mutex);
		pthread_mutex_destroy(&main->philo[i].action_mutex);
		i++;
	}
	pthread_mutex_unlock(&main->args.dead_mutex);
	pthread_mutex_destroy(&main->args.dead_mutex);
	free(main->philo);
	free(main->fork);
}
