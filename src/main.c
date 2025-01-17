/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:23:49 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:19:10 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	error_message(void)
{
	write(2, "Error! invalid arguments\n", 25);
	return (1);
}

static int	create_threads(t_diningTable *table, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, &philosopher_loop,
				&table->philosophers[i]) != 0)
		{
			write(2, "Error! cannot create thread\n", 28);
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			free(table->philosophers);
			free(threads);
			return (1);
		}
		pthread_mutex_lock(&table->check_lock);
		table->philosophers[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->check_lock);
	}
	return (0);
}

static void	print_completion_message(t_diningTable *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("All philosophers have eaten at least %d times.\n",
		table->must_eat_count);
	pthread_mutex_unlock(&table->print_lock);
}

int	initialize_simulation(t_diningTable *table)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(table->number_of_philosophers
			* sizeof(pthread_t));
	if (!threads)
	{
		fprintf(stderr, "Error: Could not allocate memory for threads.\n");
		return (1);
	}
	table->start_time = get_time();
	if (create_threads(table, threads) != 0)
	{
		free(threads);
		return (1);
	}
	monitor_death(table);
	if (table->is_full && !table->dead)
		print_completion_message(table);
	clean_up(table, threads);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_diningTable	table;

	if ((argc < 5 || argc > 6) || check_arguments(argc, argv, &table))
		return (error_message());
	if (initialize_simulation(&table) != 0)
		return (1);
	return (0);
}
