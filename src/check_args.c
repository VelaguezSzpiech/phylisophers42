/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:39 by vela              #+#    #+#             */
/*   Updated: 2025/01/05 22:42:34 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Verifies that each argument is a valid (non-negative) integer
*/
static int	validate_numeric_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		/*
		** Disallow negative sign
		*/
		if (argv[i][0] == '-')
			return (1);
		/*
		** Allow an optional plus
		*/
		else if (argv[i][0] == '+')
			j++;
		/*
		** Check that the remainder are digits
		*/
		if (!is_digit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!is_digit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

/*
** Check for overflow: if the numeric value is bigger than INT_MAX
*/
static int	verify_overflow(char *s)
{
	size_t	len;

	len = str_length(s);
	/*
	** Skip '+' sign if present
	*/
	if (*s == '+' && s++)
		len--;
	/*
	** Skip leading zeroes
	*/
	while (*s == '0' && *s && len--)
		s++;
	/*
	** If length > 10, definitely overflow
	*/
	if (len > 10)
		return (1);
	/*
	** If length < 10, definitely safe
	*/
	else if (len < 10)
		return (0);
	/*
	** If exactly 10 digits, compare to "2147483648"
	*/
	if (str_ncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

/*
** Validate all arguments for numeric correctness and overflow
*/
static int	all_args_valid(int argc, char *argv[])
{
	int	i;

	if (validate_numeric_args(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (verify_overflow(argv[i]))
			return (1);
	}
	return (0);
}

/*
** Initialize the table and philosophers
** --> Return 1 on error, 0 on success
*/
static int	initialize_table(t_diningTable *table)
{
	int	i;

	/*
	** Allocate memory for philosophers
	*/
	table->philosophers = (t_philosopher *)
		malloc(table->number_of_philosophers * sizeof(t_philosopher));
	if (!table->philosophers)
	{
		write(2, "Error! memory allocation failed\n", 31);
		return (1);
	}
	table->dead = 0;
	table->is_full = 0;
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].table = table;
		table->philosophers[i].times_eaten = 0;
		/*
		** Make the list circular
		*/
		if (i + 1 == table->number_of_philosophers)
			table->philosophers[i].next = &table->philosophers[0];
		else
			table->philosophers[i].next = &table->philosophers[i + 1];
		if (i == 0)
			table->philosophers[i].prev =
				&table->philosophers[table->number_of_philosophers - 1];
		else
			table->philosophers[i].prev = &table->philosophers[i - 1];
		pthread_mutex_init(&table->philosophers[i].fork_mutex, NULL);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->check_lock, NULL);
	return (0);
}

/*
** Public function to check arguments and populate the table structure
*/
int	check_arguments(int argc, char *argv[], t_diningTable *table)
{
	if (all_args_valid(argc, argv))
		return (1);

	table->number_of_philosophers = str_to_int(argv[1]);
	table->time_to_die = str_to_int(argv[2]);
	table->time_to_eat = str_to_int(argv[3]);
	table->time_to_sleep = str_to_int(argv[4]);
	table->must_eat_count = -1;

	if (argc == 6)
		table->must_eat_count = str_to_int(argv[5]);

	/*
	** Reject 0 or negative values for philosophers/time if you don't want them:
	*/
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
	{
		write(2, "Error! Invalid arguments (must not be zero)\n", 44);
		return (1);
	}

	/*
	** Now initialize the table
	*/
	if (initialize_table(table))
		return (1);

	return (0);
}
