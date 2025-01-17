/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:59 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:02:45 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void smart_sleep(t_diningTable *table, size_t duration)
{
    size_t start = get_time();
    while (1)
    {
        // Protect the read of 'table->dead' with the mutex
        pthread_mutex_lock(&table->check_lock);
        int dead = table->dead;
        pthread_mutex_unlock(&table->check_lock);

        if (dead)
            break; 

        if ((get_time() - start) >= duration)
            break;
        usleep(100);
    }
}

void clean_up(t_diningTable *table, pthread_t *threads)
{
    int i;

    // Join all philosopher threads (if not already joined)
    for (i = 0; i < table->number_of_philosophers; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes associated with each philosopher
    for (i = 0; i < table->number_of_philosophers; i++)
    {
        pthread_mutex_destroy(&table->philosophers[i].fork_mutex);
    }

    // Destroy table-level mutexes
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->check_lock);

    // Free allocated memory
    free(table->philosophers);
    free(threads);
}
