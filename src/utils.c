/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:06:12 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/28 18:03:36 by crigonza         ###   ########.fr       */
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

void	print_actions(t_philo *philo)
{
	unsigned int	time;

	time = get_time() - philo->args->start;
	if (!philo->args->is_dead)
	{
		if (philo->state == TAKEFORK)
			printf("%u %d has taken a fork\n", time, philo->id);
		if (philo->state == EATING)
			printf("%u %d is eating\n", time, philo->id);
		if (philo->state == SLEEPING)
			printf("%u %d is sleeping\n", time, philo->id);
		if (philo->state == THINKING)
			printf("%u %d is thinking\n", time, philo->id);
	}
	if (philo->state == DEAD)
		printf("%u %d died\n", time, philo->id);
}

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	take_time(int time)
{
	int	start;
	int	now;

	now = 0;
	start = (int)get_time();
	while (time != now)
	{
		usleep(10);
		now = get_time() - start;
	}
}
