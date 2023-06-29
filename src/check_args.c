/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:33:11 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/29 08:16:13 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;
	int number;

	i = 1;
	while (i < argc)
	{
		j = 0;
		number = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= 48 && argv[i][j] <= 57)
				number ++;
			j++;
		}
		if (!number)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv, t_main *main)
{
	if (!valid_args(argc, argv))
	{
		printf("Error, invalid arguments!\n");
		return(0);
	}
	if (argc == 5 || argc == 6)
	{
		main->args.is_dead = 0;
		main->args.n_of_philos = ph_atoi(argv[1]);
		main->args.time_to_die = ph_atoi(argv[2]);
		main->args.time_to_eat = ph_atoi(argv[3]);
		main->args.time_to_sleep = ph_atoi(argv[4]);
		main->args.start = get_time();
		pthread_mutex_init(&main->args.dead_mutex, NULL);
		main->args.must_eat_count = main->args.n_of_philos;
		if (argc == 6)
			main->args.times_must_eat = ph_atoi(argv[5]);
		else
			main->args.times_must_eat = -1;
	}
	else
	{
		printf("Error, invalid arguments!\n");
		return(0);
	}
	return (1);
}

void	args_error(void)
{
	printf("Error, invalid arguments!\n");
}
