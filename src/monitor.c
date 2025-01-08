/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:45:00 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 20:02:26 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Check if a philosopher has died
*/
static int	check_philosopher_death(t_philosopher *philosopher)
{
	t_diningTable	*table;

	table = philosopher->table;
	pthread_mutex_lock(&table->check_lock);
	if (get_time() - philosopher->last_meal > (size_t)table->time_to_die)
	{
		print_message(philosopher, MESSAGE_DEAD);
		table->dead = 1;
		pthread_mutex_unlock(&table->check_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->check_lock);
	return (0);
}

/*
** Check if all philosophers have eaten the required number of times
*/
static int	check_philosophers_full(t_diningTable *table)
{
	int	i;

	i = 0;
	while (table->must_eat_count != -1 && i < table->number_of_philosophers
		&& table->philosophers[i].times_eaten >= table->must_eat_count)
		i++;
	if (i == table->number_of_philosophers)
	{
		table->is_full = 1;
		return (1);
	}
	return (0);
}

/*
** Monitor philosophers for death or completion
*/
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
