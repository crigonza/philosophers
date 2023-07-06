/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:06:12 by crigonza          #+#    #+#             */
/*   Updated: 2023/07/06 08:21:49 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ph_atoi(const char *nptr)
{
	int			i;
	long int	n;
	long int	result;

	i = 0;
	result = 0;
	n = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result * n);
}

void	print_actions(t_philo *philo, char *state)
{
	int				is_dead;
	unsigned int	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->dead_mutex);
		is_dead = philo->args->is_dead;
	pthread_mutex_unlock(&philo->args->dead_mutex);
	pthread_mutex_lock(&philo->dead_lock);
	if (state[0] == 'd')
		printf("%u %d %s\n", time, philo->id, state);
	if (!is_dead)
		printf("%u %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->dead_lock);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	take_time(long int time)
{
	long int	start;

	start = get_time();
	usleep((time / 2) * 1000);
	while (time > (get_time() - start))
		usleep(50);
}
