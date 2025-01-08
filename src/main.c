/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:46 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 19:45:38 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	error_message(void)
{
	write(2, "Error! invalid arguments\n", 25);
	return (1);
}

/*
** Function to create threads for philosophers
*/
static int	create_threads(t_diningTable *table, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL,
				&routine, &table->philosophers[i]) != 0)
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

/*
** Function to initialize threads and start monitoring
*/
static int	initialize_simulation(t_diningTable *table)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(table->number_of_philosophers
			* sizeof(pthread_t));
	if (!threads)
	{
		write(2, "Error! memory allocation failed\n", 31);
		free(table->philosophers);
		return (1);
	}
	table->start_time = get_time();
	if (create_threads(table, threads) != 0)
		return (1);
	monitor_death(table);
	clean_up(table, threads);
	return (0);
}

/*
** Main function to handle argument parsing and simulation initialization
*/
int	main(int argc, char *argv[])
{
	t_diningTable	table;

	if ((argc < 5 || argc > 6) || check_arguments(argc, argv, &table))
		return (error_message());
	if (initialize_simulation(&table) != 0)
		return (1);
	return (0);
}
