/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:26:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/04 21:36:27 by crigonza         ###   ########.fr       */
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
		pthread_mutex_init(&main->philo[i].action_mutex, NULL);
		if (i != 0)
			main->philo[i].left_fork = &main->fork[i - 1];
		main->philo[i].right_fork = &main->fork[i];
		pthread_mutex_init(&main->fork[i].mutex, NULL);
		i++;
	}
	i--;
	main->philo[0].left_fork = &main->fork[i];
}

int	pick_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left_fork->mutex) == 0)
	{
		// pthread_mutex_lock(&philo->action_mutex);
		philo->state = TAKEFORK;
		print_actions(philo);
		// pthread_mutex_unlock(&philo->action_mutex);
		if (pthread_mutex_lock(&philo->right_fork->mutex) == 0)
		{
			// pthread_mutex_lock(&philo->action_mutex);
			philo->state = TAKEFORK;
			print_actions(philo);
			// pthread_mutex_unlock(&philo->action_mutex);
		}
		else
		{
			pthread_mutex_unlock(&philo->left_fork->mutex);
			return(0);
		}
	}
	return (1);
}

int	philo_is_eating(t_philo *philo)
{
	/* pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex); */
	if (!pick_forks(philo))
		return (0);
	/* pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex); */
	//pthread_mutex_lock(&philo->action_mutex);

	pthread_mutex_lock(&philo->action_mutex);
	philo->last_time = get_time();
	pthread_mutex_unlock(&philo->action_mutex);
	philo->state = EATING;
	print_actions(philo);
	pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->times_must_eat != -1)
		check_meals(philo);
	pthread_mutex_unlock(&philo->args->dead_mutex);
	take_time(philo->args->time_to_eat);
	// pthread_mutex_unlock(&philo->action_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	/* pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex); */
	philo->state = SLEEPING;
	print_actions(philo);
	take_time(philo->args->time_to_sleep);
	return (1);
}

int	philo_is_thinking(t_philo *philo)
{
	/* pthread_mutex_lock(&philo->args->dead_mutex);
	if (philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->dead_mutex); */
	philo->state = THINKING;
	print_actions(philo);
	return (1);
}
