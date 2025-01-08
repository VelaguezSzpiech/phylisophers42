/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:39 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 19:42:50 by vela             ###   ########.fr       */
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
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
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

static int	verify_overflow(char *s)
{
	size_t	len;

	len = str_length(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
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
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
	{
		write(2, "Error! Invalid arguments (must not be zero)\n", 44);
		return (1);
	}
	if (initialize_table(table))
		return (1);
	return (0);
}
