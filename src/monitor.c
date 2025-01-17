/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:55 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:18:47 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_philosopher_death(t_philosopher *philosopher)
{
    t_diningTable *table = philosopher->table;
    pthread_mutex_lock(&table->check_lock);

    if (get_time() - philosopher->last_meal > (size_t)table->time_to_die)
    {
        table->dead = 1;
        print_message(philosopher, MESSAGE_DEAD);
        pthread_mutex_unlock(&table->check_lock);
        return 1;
    }

    pthread_mutex_unlock(&table->check_lock);
    return 0;
}

static int	check_philosophers_full(t_diningTable *table)
{
	int	i;

	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	pthread_mutex_lock(&table->check_lock);
	if (table->is_full)
	{
		pthread_mutex_unlock(&table->check_lock);
		return (1);
	}
	while (i < table->number_of_philosophers)
	{
		if (table->philosophers[i].times_eaten < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->check_lock);
			return (0);
		}
		i++;
	}
	table->is_full = 1;
	pthread_mutex_unlock(&table->check_lock);
	return (1);
}

void	monitor_death(t_diningTable *table)
{
	int	i;

	while (!table->is_full && !table->dead)
	{
		i = -1;
		while (++i < table->number_of_philosophers && !table->dead)
		{
			if (check_philosopher_death(&table->philosophers[i]))
				return ;
		}
		if (check_philosophers_full(table))
			return ;
		usleep(100);
	}
}
