/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:28 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/14 23:53:00 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *philo_actions(void *args)
{
    t_philo *philo;
    // unsigned int time = get_time();

    philo = (t_philo*)args;
    while(1)
    {
        /* if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
            printf(" %d is thinking\n", philo->id);
        else
        {
            print_actions(philo, 1);
            pthread_mutex_unlock(&philo->left_fork->mutex);
            print_actions(philo, 1);
            printf(" %d is eating\n", philo->id);
            usleep(philo->args->time_to_eat * 1000);
            pthread_mutex_unlock(&philo->left_fork->mutex);
            pthread_mutex_unlock(&philo->right_fork->mutex);
            printf(" %d is sleeping\n", philo->id);
            usleep(philo->args->time_to_sleep * 1000);
        } */
        if(philo_is_eating(philo) != 0)
            philo_is_sleeping(philo);
        philo_is_sleeping(philo);
        print_actions(philo, 4);
        /* if(!philo_is_eating(philo))
            print_actions(philo->id, 4);*/
        
    }
    return (NULL);
}