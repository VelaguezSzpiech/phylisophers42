/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:44 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 20:42:40 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <sys/time.h>  // <-- For gettimeofday

/*
** Returns the current time in milliseconds
*/
size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
** Sleeps in small increments until the desired duration has passed
** or until the simulation is marked dead (table->dead == 1).
*/
void	smart_sleep(t_diningTable *table, size_t duration)
{
	size_t	start;
	size_t	now;

	start = get_time();
	while (!table->dead)
	{
		now = get_time();
		if ((now - start) >= duration)
			break ;
		usleep(100);
	}
}

/*
** Clean-up function to join philosopher threads,
** destroy mutexes, and free memory allocations
*/
void	clean_up(t_diningTable *table, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_mutex_destroy(&table->philosophers[i].fork_mutex);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->check_lock);
	free(table->philosophers);
	free(threads);
}
