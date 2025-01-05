/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:49 by vela              #+#    #+#             */
/*   Updated: 2025/01/05 22:42:25 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** The philosopher attempts to eat:
** Locks its own fork, then the next fork
** Updates last_meal, increments times_eaten, and sleeps the eating duration
*/
static void	philosopher_eat(t_philosopher *philosopher)
{
	t_diningTable	*table;

	table = philosopher->table;
	pthread_mutex_lock(&philosopher->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);
	if (table->number_of_philosophers == 1)
	{
		smart_sleep(table, table->time_to_die);
		print_message(philosopher, MESSAGE_DEAD);
		pthread_mutex_unlock(&philosopher->fork_mutex);
		table->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philosopher->next->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);

	pthread_mutex_lock(&table->check_lock);
	philosopher->times_eaten++;
	print_message(philosopher, MESSAGE_EATING);
	philosopher->last_meal = get_time();
	pthread_mutex_unlock(&table->check_lock);

	smart_sleep(table, table->time_to_eat);

	pthread_mutex_unlock(&philosopher->fork_mutex);
	pthread_mutex_unlock(&philosopher->next->fork_mutex);
}

/*
** The main routine for each philosopher thread
*/
void	*routine(void *arg)
{
	t_philosopher	*philosopher;
	t_diningTable	*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;

	/*
	** Small delay for even-numbered philosophers to avoid immediate deadlocks
	*/
	if (philosopher->id % 2 == 0)
		usleep(1000);

	while (!table->dead && !table->is_full)
	{
		philosopher_eat(philosopher);
		print_message(philosopher, MESSAGE_SLEEPING);
		smart_sleep(table, table->time_to_sleep);
		print_message(philosopher, MESSAGE_THINKING);
	}
	return (NULL);
}
