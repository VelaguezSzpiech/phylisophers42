/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:49 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 20:44:34 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philosopher_eat(t_philosopher *philosopher)
{
	t_diningTable	*table;

	table = philosopher->table;
	pthread_mutex_lock(&philosopher->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);
	pthread_mutex_lock(&philosopher->next->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);
	pthread_mutex_lock(&table->check_lock);
	philosopher->last_meal = get_time();
	philosopher->times_eaten++;
	print_message(philosopher, MESSAGE_EATING);
	pthread_mutex_unlock(&table->check_lock);
	smart_sleep(table, table->time_to_eat);
	pthread_mutex_unlock(&philosopher->fork_mutex);
	pthread_mutex_unlock(&philosopher->next->fork_mutex);
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 == 0)
		usleep(1000);
	while (!philosopher->table->dead && !philosopher->table->is_full)
	{
		philosopher_eat(philosopher);
		print_message(philosopher, MESSAGE_SLEEPING);
		smart_sleep(philosopher->table, philosopher->table->time_to_sleep);
		print_message(philosopher, MESSAGE_THINKING);
	}
	return (NULL);
}
