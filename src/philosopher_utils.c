/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:59 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/19 15:57:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(t_diningTable *table, size_t duration)
{
	size_t	start;
	int		dead;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&table->check_lock);
		dead = table->dead;
		pthread_mutex_unlock(&table->check_lock);
		if (dead)
			break ;
		if ((get_time() - start) >= duration)
			break ;
		usleep(100);
	}
}

void	clean_up(t_diningTable *table, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
	}
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&table->philosophers[i].fork_mutex);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->check_lock);
	free(table->philosophers);
	free(threads);
}
