/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:24:08 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:02:12 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void philosopher_eat(t_philosopher *philosopher)
{
    t_diningTable *table = philosopher->table;
    int first_id = philosopher->id < philosopher->next->id ? philosopher->id : philosopher->next->id;
    int second_id = philosopher->id < philosopher->next->id ? philosopher->next->id : philosopher->id;
    t_philosopher *first_fork_owner = (philosopher->id == first_id) ? philosopher : philosopher->next;
    t_philosopher *second_fork_owner = (philosopher->id == second_id) ? philosopher : philosopher->next;

    // Lock first fork
    pthread_mutex_lock(&first_fork_owner->fork_mutex);
    print_message(philosopher, MESSAGE_FORK);

    // If there's only one philosopher, handle special case
    if (table->number_of_philosophers == 1)
    {
        smart_sleep(table, table->time_to_die);
        pthread_mutex_lock(&table->check_lock);
        print_message(philosopher, MESSAGE_DEAD);
        table->dead = 1;
        pthread_mutex_unlock(&table->check_lock);
        pthread_mutex_unlock(&first_fork_owner->fork_mutex);
        return;
    }

    // Lock second fork
    pthread_mutex_lock(&second_fork_owner->fork_mutex);
    print_message(philosopher, MESSAGE_FORK);

    // Update last meal time safely
    pthread_mutex_lock(&table->check_lock);
    philosopher->last_meal = get_time();
    philosopher->times_eaten++;
    print_message(philosopher, MESSAGE_EATING);
    pthread_mutex_unlock(&table->check_lock);

    // Eat
    smart_sleep(table, table->time_to_eat);

    // Unlock both forks
    pthread_mutex_unlock(&second_fork_owner->fork_mutex);
    pthread_mutex_unlock(&first_fork_owner->fork_mutex);
}

void	perform_actions(t_philosopher *philosopher)
{
	philosopher_eat(philosopher);
	print_message(philosopher, MESSAGE_SLEEPING);
	smart_sleep(philosopher->table, philosopher->table->time_to_sleep);
	print_message(philosopher, MESSAGE_THINKING);
}

void *philosopher_loop(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;
    t_diningTable *table = philosopher->table;

    // Optional: Small delay to prevent all philosophers from starting at the same time
    if (philosopher->id % 2 == 0)
        usleep(1000);

    while (1)
    {
        // Check termination conditions
        pthread_mutex_lock(&table->check_lock);
        if (table->dead || table->is_full)
        {
            pthread_mutex_unlock(&table->check_lock);
            break; // Exit the loop gracefully
        }
        pthread_mutex_unlock(&table->check_lock);

        // Perform eating, sleeping, thinking actions
        perform_actions(philosopher);
    }

    return NULL; // Thread exits cleanly
}
