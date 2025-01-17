/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:24:08 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:47:52 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	assign_forks(t_philosopher *philosopher, t_fork_info *fork_info)
{
	t_philosopher	*next;

	next = philosopher->next;
	if (philosopher->id < next->id)
	{
		fork_info->first_fork_owner = philosopher;
		fork_info->second_fork_owner = next;
	}
	else
	{
		fork_info->first_fork_owner = next;
		fork_info->second_fork_owner = philosopher;
	}
}

void	lock_and_eat(t_philosopher *philosopher, t_fork_info *fork_info)
{
	t_diningTable	*table;

	table = philosopher->table;
	pthread_mutex_lock(&fork_info->first_fork_owner->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);
	pthread_mutex_lock(&fork_info->second_fork_owner->fork_mutex);
	print_message(philosopher, MESSAGE_FORK);
	pthread_mutex_lock(&table->check_lock);
	philosopher->last_meal = get_time();
	philosopher->times_eaten++;
	print_message(philosopher, MESSAGE_EATING);
	pthread_mutex_unlock(&table->check_lock);
	smart_sleep(table, table->time_to_eat);
	pthread_mutex_unlock(&fork_info->second_fork_owner->fork_mutex);
	pthread_mutex_unlock(&fork_info->first_fork_owner->fork_mutex);
}

void	handle_single_philosopher(t_diningTable *table,
		t_philosopher *philosopher)
{
	smart_sleep(table, table->time_to_die);
	pthread_mutex_lock(&table->check_lock);
	print_message(philosopher, MESSAGE_DEAD);
	table->dead = 1;
	pthread_mutex_unlock(&table->check_lock);
	pthread_mutex_unlock(&philosopher->fork_mutex);
}

void	philosopher_eat(t_philosopher *philosopher)
{
	t_diningTable	*table;
	t_fork_info		fork_info;

	table = philosopher->table;
	assign_forks(philosopher, &fork_info);
	if (table->number_of_philosophers == 1)
	{
		handle_single_philosopher(table, philosopher);
		return ;
	}
	lock_and_eat(philosopher, &fork_info);
}

void	*philosopher_loop(void *arg)
{
	t_philosopher	*philosopher;
	t_diningTable	*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;
	if (philosopher->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&table->check_lock);
		if (table->dead || table->is_full)
		{
			pthread_mutex_unlock(&table->check_lock);
			break ;
		}
		pthread_mutex_unlock(&table->check_lock);
		philosopher_eat(philosopher);
		print_message(philosopher, MESSAGE_SLEEPING);
		smart_sleep(table, table->time_to_sleep);
		print_message(philosopher, MESSAGE_THINKING);
	}
	return (NULL);
}
