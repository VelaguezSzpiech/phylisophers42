/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:44 by vela              #+#    #+#             */
/*   Updated: 2025/01/05 22:42:13 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Continually checks if a philosopher has died or if everyone is full
*/
void	monitor_death(t_diningTable *table)
{
	int	i;

	while (!table->is_full)
	{
		i = -1;
		while (!table->dead && ++i < table->number_of_philosophers)
		{
			pthread_mutex_lock(&table->check_lock);
			if (get_time() - table->philosophers[i].last_meal >
				(size_t)table->time_to_die)
			{
				print_message(&table->philosophers[i], MESSAGE_DEAD);
				table->dead = 1;
			}
			pthread_mutex_unlock(&table->check_lock);
			usleep(100);
		}
		if (table->dead)
			break ;
		/*
		** Check if all have eaten enough times (only if must_eat_count != -1)
		*/
		i = 0;
		while (table->must_eat_count != -1 && i < table->number_of_philosophers
			&& table->philosophers[i].times_eaten >= table->must_eat_count)
			i++;
		if (i == table->number_of_philosophers)
			table->is_full = 1;
	}
}

/*
** Join threads, destroy mutexes, free memory
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

/*
** Get the current time in ms
*/
size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
** Sleep, but also check if someone died in the meantime
*/
void	smart_sleep(t_diningTable *table, size_t duration)
{
	size_t	start;

	start = get_time();
	while (!table->dead)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(100);
	}
}
