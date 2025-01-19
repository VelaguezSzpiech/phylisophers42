/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:24:08 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/19 15:43:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
void    assign_forks(t_philosopher *philosopher, t_fork_info *fork_info)
{
    if (philosopher->id % 2 == 0)
    {
        fork_info->first_fork_owner = philosopher->next;
        fork_info->second_fork_owner = philosopher;
    }
    else
    {
        fork_info->first_fork_owner = philosopher;
        fork_info->second_fork_owner = philosopher->next;
    }
}

void    lock_and_eat(t_philosopher *philosopher, t_fork_info *fork_info)
{
    t_diningTable    *table;

    table = philosopher->table;
    pthread_mutex_lock(&fork_info->first_fork_owner->fork_mutex);
    print_message(philosopher, MESSAGE_FORK);
    pthread_mutex_lock(&fork_info->second_fork_owner->fork_mutex);
    print_message(philosopher, MESSAGE_FORK);
    
    pthread_mutex_lock(&table->check_lock);
    philosopher->last_meal = get_time();
    philosopher->times_eaten++;
    pthread_mutex_unlock(&table->check_lock);
    
    print_message(philosopher, MESSAGE_EATING);
    smart_sleep(table, table->time_to_eat);
    
    pthread_mutex_unlock(&fork_info->second_fork_owner->fork_mutex);
    pthread_mutex_unlock(&fork_info->first_fork_owner->fork_mutex);
}

void    philosopher_eat(t_philosopher *philosopher)
{
    t_diningTable    *table;
    t_fork_info      fork_info;

    table = philosopher->table;
    if (table->number_of_philosophers == 1)
    {
        print_message(philosopher, MESSAGE_FORK);
        smart_sleep(table, table->time_to_die);
        return;
    }
    assign_forks(philosopher, &fork_info);
    lock_and_eat(philosopher, &fork_info);
}

void    *philosopher_loop(void *arg)
{
    t_philosopher    *philosopher;
    t_diningTable    *table;
    int              continue_loop;

    philosopher = (t_philosopher *)arg;
    table = philosopher->table;
    if (philosopher->id % 2 == 0)
        usleep(1000);
    
    while (1)
    {
        pthread_mutex_lock(&table->check_lock);
        continue_loop = (!table->dead && !table->is_full);
        pthread_mutex_unlock(&table->check_lock);
        
        if (!continue_loop)
            break;
            
        philosopher_eat(philosopher);
        print_message(philosopher, MESSAGE_SLEEPING);
        smart_sleep(table, table->time_to_sleep);
        print_message(philosopher, MESSAGE_THINKING);
    }
    return (NULL);
}
