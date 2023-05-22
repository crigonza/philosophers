/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:33:11 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/19 13:15:17 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void check_args(int argc, char **argv, t_main *main)
{
    if (argc == 5 || argc == 6)
    {
        main->args.n_of_philos = ph_atoi(argv[1]);
        main->args.time_to_die = ph_atoi(argv[2]);
        main->args.time_to_eat = ph_atoi(argv[3]);
        main->args.time_to_sleep = ph_atoi(argv[4]);
        if(argc == 6)
            main->args.number_of_times_each_filosopher_must_eat = ph_atoi(argv[5]);
        else
            main->args.number_of_times_each_filosopher_must_eat = 0;
    }
    else
        args_error();
}

void args_error(void)
{
    printf("Error, invalid arguments number!\n");
}