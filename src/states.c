/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:28 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/06 08:21:08 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_meals(t_philo *philo)
{
	if (philo->meals < philo->args->times_must_eat)
	{
		pthread_mutex_lock(&philo->last_time_mutex);
		philo->meals++;
		pthread_mutex_unlock(&philo->last_time_mutex);
	}
	if (philo->meals == philo->args->times_must_eat)
	{
		pthread_mutex_lock(&philo->args->dead_mutex);
		if (philo->args->must_eat_count != 0)
			philo->args->must_eat_count--;
		pthread_mutex_unlock(&philo->args->dead_mutex);
	}
}

void	*check_state(t_main *main)
{
	int	i;
	int	last;
	int	meals;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&main->philo[i].last_time_mutex);
		meals = main->philo[i].meals;
		last = main->philo[i].last_time;
		pthread_mutex_unlock(&main->philo[i].last_time_mutex);
		if (meals == main->philo->args->times_must_eat)
			return (NULL);
		if ((int)(get_time() - last) > (main->philo->args->time_to_die))
		{
			pthread_mutex_lock(&main->philo->args->dead_mutex);
			main->philo->args->is_dead = 1;
			pthread_mutex_unlock(&main->philo->args->dead_mutex);
			print_actions(&main->philo[i], "died");
			return (NULL);
		}
		if (i == main->args.n_of_philos - 1)
			i = -1;
		i++;
	}
}

void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_actions(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_actions(philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_time_mutex);
	philo->last_time = get_time();
	pthread_mutex_unlock(&philo->last_time_mutex);
	print_actions(philo, "is eating");
	if (philo->args->times_must_eat != -1)
		check_meals(philo);
	take_time(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	print_actions(philo, "is sleeping");
	take_time(philo->args->time_to_sleep);
	print_actions(philo, "is thinking");
}

void	*philo_actions(void *args)
{
	t_philo	*philo;
	int		died;
	int		meals;

	philo = (t_philo *)args;
	died = 0;
	while (!died && meals != 0)
	{
		pthread_mutex_lock(&philo->args->dead_mutex);
		died = philo->args->is_dead;
		meals = philo->args->must_eat_count;
		pthread_mutex_unlock(&philo->args->dead_mutex);
		if (philo->args->n_of_philos == 1)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			print_actions(philo, "has taken a fork");
			break ;
		}
		philo_routine(philo);
		//pthread_mutex_lock(&philo->args->dead_mutex);
	}
	//pthread_mutex_unlock(&philo->args->dead_mutex);
	return (NULL);
}
