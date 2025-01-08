/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:53 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 20:41:24 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*
** Renamed messages
*/
enum e_message
{
	MESSAGE_FORK = 0,
	MESSAGE_EATING,
	MESSAGE_SLEEPING,
	MESSAGE_THINKING,
	MESSAGE_DEAD
};

/*
** Renamed struct for philosopher
*/
typedef struct s_philosopher
{
	int						id;
	int						times_eaten;
	size_t					last_meal;
	pthread_mutex_t			fork_mutex;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	struct s_diningTable	*table;
}	t_philosopher;

/*
** Renamed struct for the dining table
*/
typedef struct s_diningTable
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				number_of_philosophers;
	int				is_full;
	int				dead;
	size_t			start_time;
	t_philosopher	*philosophers;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	check_lock;
}	t_diningTable;

/* Renamed prototypes */
int		is_digit(int c);
size_t	str_length(const char *s);
int		str_ncmp(const char *s1, const char *s2, size_t n);
int		str_to_int(const char *str);
int		initialize_table(t_diningTable *table);
void	monitor_death(t_diningTable *table);

int		check_arguments(int argc, char *argv[], t_diningTable *table);
void	print_message(t_philosopher *philosopher, int message);
void	*routine(void *arg);
void	monitor_death(t_diningTable *table);
void	clean_up(t_diningTable *table, pthread_t *threads);
size_t	get_time(void);
void	smart_sleep(t_diningTable *table, size_t duration);

#endif
