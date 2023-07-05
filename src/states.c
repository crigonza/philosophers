/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:28 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/05 18:32:44 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->n_of_philos)
	{
		if (philo[i].meals == philo->args->times_must_eat)
			return (0);
		pthread_mutex_lock(&philo->action_mutex);
		if ((int)(get_time() - philo[i].last_time) > (philo->args->time_to_die))
		{
			philo[i].state = DEAD;
			pthread_mutex_unlock(&philo->action_mutex);
			pthread_mutex_lock(&philo->args->dead_mutex);
			philo->args->is_dead = 1;
			pthread_mutex_unlock(&philo->args->dead_mutex);
			print_actions(&philo[i]);
			return (0);
		}
		pthread_mutex_unlock(&philo->action_mutex);
		i++;
	}
	return (1);
}

void	check_meals(t_philo *philo)
{
	if (philo->meals < philo->args->times_must_eat)
		philo->meals++;
	if (philo->meals == philo->args->times_must_eat)
	{
		if (philo->args->must_eat_count != 0)
			philo->args->must_eat_count--;
	}
}

void	*check_state(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		// pthread_mutex_lock(&philo->args->dead_mutex);
		if (!check_death(philo))
			return (0);
		// pthread_mutex_unlock(&philo->args->dead_mutex);
	}
	return (NULL);
}

void philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->state = TAKEFORK;
	print_actions(philo);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->state = TAKEFORK;
	print_actions(philo);
	pthread_mutex_lock(&philo->action_mutex);
	philo->last_time = get_time();
	pthread_mutex_unlock(&philo->action_mutex);
	philo->state = EATING;
	print_actions(philo);
	if (philo->args->times_must_eat != -1)
		check_meals(philo);
	take_time(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->state = SLEEPING;
	print_actions(philo);
	take_time(philo->args->time_to_sleep);
	philo->state = THINKING;
	print_actions(philo);
}

void	*philo_actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->args->dead_mutex);
	while (!philo->args->is_dead && philo->args->must_eat_count != 0)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		/* if (philo->args->n_of_philos == 1)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			print_actions(philo);
			break ;
		} */
		
		philo_routine(philo);
		// /* if (!philo->args->must_eat_count)
		// 	break ; */
		// if (philo_is_eating(philo))
		// {
		// 	/* if (!philo->args->must_eat_count)
		// 		break ; */
		// 	if (!philo_is_sleeping(philo))
		// 		break;
		// }
		// /* if (!philo->args->must_eat_count)
		// 	break ; */
		// if (!philo_is_thinking(philo))
		// 	break ;
		// pthread_mutex_lock(&philo->args->dead_mutex);
	}
	// pthread_mutex_unlock(&philo->args->dead_mutex);
	return (NULL);
}
