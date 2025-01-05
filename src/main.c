/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:46 by vela              #+#    #+#             */
/*   Updated: 2025/01/05 22:42:31 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Simple error function
*/
static int	error_message(void)
{
	write(2, "Error! invalid arguments\n", 25);
	return (1);
}

/*
** Entry point
*/
int	main(int argc, char *argv[])
{
	int				i;
	t_diningTable	table;
	pthread_t		*threads;
	int				created_threads;

	if ((argc < 5 || argc > 6) || check_arguments(argc, argv, &table))
		return (error_message());

	threads = (pthread_t *)malloc(table.number_of_philosophers * sizeof(pthread_t));
	if (!threads)
	{
		write(2, "Error! memory allocation failed\n", 31);
		/*
		** table->philosophers was already allocated in check_arguments
		** Clean up philosophers:
		*/
		free(table.philosophers);
		return (1);
	}

	table.start_time = get_time();
	i = -1;
	created_threads = 0;
	while (++i < table.number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, &routine, &table.philosophers[i]) != 0)
		{
			write(2, "Error! cannot create thread\n", 28);
			/*
			** Gracefully join threads already created
			*/
			for (int j = 0; j < i; j++)
				pthread_join(threads[j], NULL);

			free(table.philosophers);
			free(threads);
			return (1);
		}
		created_threads++;
		pthread_mutex_lock(&table.check_lock);
		table.philosophers[i].last_meal = table.start_time;
		pthread_mutex_unlock(&table.check_lock);
	}

	/*
	** Start monitoring
	*/
	monitor_death(&table);

	/*
	** Clean everything up
	*/
	clean_up(&table, threads);
	return (0);
}
