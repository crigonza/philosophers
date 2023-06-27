/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:28 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/27 19:19:19 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int check_death(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->args->n_of_philos)
    {
        if (philo[i].meals == philo->args->times_must_eat)
            return (0);
        if((int)(get_time() - philo[i].last_time) > (philo->args->time_to_die))
        {
            philo[i].state = DEAD;
            philo->args->is_dead = 1;
            pthread_mutex_lock(&philo[i].dead_lock);
            print_actions(&philo[i]);
            return(0);
        }
        i++;
    }
    return(1);
}

void    *check_state(void *args)
{
    t_philo *philo;
    
    philo = (t_philo*)args;
    while(1)
    {
       if (!check_death(philo))
        return(0);
    }
    return(NULL);
}

void    *philo_actions(void *args)
{
    t_philo *philo;

    philo = (t_philo*)args;
    while(1)
    {
        if (philo->args->n_of_philos == 1)
        {
            pthread_mutex_lock(&philo->left_fork->mutex);
            print_actions(philo);
            break;
        }
        if (philo->args->is_dead || !philo->args->must_eat_count)
            break;
        if (philo_is_eating(philo))
        {
            if(philo->args->is_dead || !philo->args->must_eat_count)
                break;
            philo_is_sleeping(philo);
        }
        if (philo->args->is_dead || !philo->args->must_eat_count)
            break;
        philo->state = THINKING;
        print_actions(philo);
    }
    return (NULL);
}