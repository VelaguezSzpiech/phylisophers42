/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:55 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/19 15:57:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_philosopher_death(t_philosopher *philosopher)
{
    t_diningTable    *table;
    size_t           current_time;
    size_t           last_meal_time;

    table = philosopher->table;
    pthread_mutex_lock(&table->check_lock);
    current_time = get_time();
    last_meal_time = philosopher->last_meal;
    if (current_time - last_meal_time > (size_t)table->time_to_die && !table->dead)
    {
        table->dead = 1;
        pthread_mutex_unlock(&table->check_lock);
        print_message(philosopher, MESSAGE_DEAD);
        return (1);
    }
    pthread_mutex_unlock(&table->check_lock);
    return (0);
}



void    monitor_death(t_diningTable *table)
{
    int    i;
    int    all_ate_enough;

    while (1)
    {
        i = -1;
        while (++i < table->number_of_philosophers)
        {
            if (check_philosopher_death(&table->philosophers[i]))
                return;
        }
        
        if (table->must_eat_count != -1)
        {
            all_ate_enough = 1;
            pthread_mutex_lock(&table->check_lock);
            i = -1;
            while (++i < table->number_of_philosophers)
            {
                if (table->philosophers[i].times_eaten < table->must_eat_count)
                {
                    all_ate_enough = 0;
                    break;
                }
            }
            if (all_ate_enough)
                table->is_full = 1;
            pthread_mutex_unlock(&table->check_lock);
            if (all_ate_enough)
                return;
        }
        usleep(1000);
    }
}
