/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:41 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 13:08:28 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	allocate_philosophers(t_diningTable *table)
{
	table->philosophers = (t_philosopher *)
		malloc(table->number_of_philosophers * sizeof(t_philosopher));
	if (!table->philosophers)
	{
		write(2, "Error! memory allocation failed\n", 31);
		return (1);
	}
	table->dead = 0;
	table->is_full = 0;
	return (0);
}

static void	init_philo(t_philosopher *philosopher, int id, t_diningTable *table)
{
	philosopher->id = id + 1;
	philosopher->table = table;
	philosopher->times_eaten = 0;
	pthread_mutex_init(&philosopher->fork_mutex, NULL);
}

static void	link_philosophers(t_philosopher *philosophers, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (i + 1 == count)
			philosophers[i].next = &philosophers[0];
		else
			philosophers[i].next = &philosophers[i + 1];
		if (i == 0)
			philosophers[i].prev = &philosophers[count - 1];
		else
			philosophers[i].prev = &philosophers[i - 1];
	}
}

static void	initialize_table_locks(t_diningTable *table)
{
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->check_lock, NULL);
}

int	initialize_table(t_diningTable *table)
{
	int	i;

	i = -1;
	if (allocate_philosophers(table))
		return (1);
	while (++i < table->number_of_philosophers)
		init_philo(&table->philosophers[i], i, table);
	link_philosophers(table->philosophers, table->number_of_philosophers);
	initialize_table_locks(table);
	return (0);
}
