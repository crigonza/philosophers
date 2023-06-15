/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:28 by crigonza          #+#    #+#             */
/*   Updated: 2023/06/15 13:04:56 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int    check_death(t_philo *philo)
{
    if((int)(get_time() - philo->last) > (philo->args->time_to_die))
    {
        print_actions(philo, 5);
        philo->death = 1;
        return(0);
    }
    return(1);
}

void    *philo_actions(void *args)
{
    t_philo *philo;

    philo = (t_philo*)args;
    while(1)
    {
        if(philo->death || !check_death(philo))
            break;
        if(philo_is_eating(philo))
        {
            if(!philo->death)
                philo_is_sleeping(philo);
        }
        if(philo->death || !check_death(philo))
            break;
        print_actions(philo, 4);
    }
    return (NULL);
}