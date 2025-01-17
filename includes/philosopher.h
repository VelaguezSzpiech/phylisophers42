/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:25:11 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:49:33 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum						e_message
{
	MESSAGE_FORK = 0,
	MESSAGE_EATING,
	MESSAGE_SLEEPING,
	MESSAGE_THINKING,
	MESSAGE_DEAD
};

typedef struct s_philosopher
{
	int						id;
	int						times_eaten;
	size_t					last_meal;
	pthread_mutex_t			fork_mutex;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	struct s_diningTable	*table;
}							t_philosopher;

typedef struct s_diningTable
{
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	int						number_of_philosophers;
	int						is_full;
	int						dead;
	size_t					start_time;
	t_philosopher			*philosophers;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			check_lock;
	pthread_cond_t			termination_cond;
}							t_diningTable;
typedef struct s_fork_info
{
	t_philosopher			*first_fork_owner;
	t_philosopher			*second_fork_owner;
}							t_fork_info;
// Function declarations
int							is_digit(int c);
size_t						str_length(const char *s);
int							str_ncmp(const char *s1, const char *s2, size_t n);
int							str_to_int(const char *str);
int							initialize_table(t_diningTable *table);
void						monitor_death(t_diningTable *table);
void						*philosopher_loop(void *arg);

int							check_arguments(int argc, char *argv[],
								t_diningTable *table);
void						print_message(t_philosopher *philosopher,
								int message);
void						clean_up(t_diningTable *table, pthread_t *threads);
size_t						get_time(void);
void						smart_sleep(t_diningTable *table, size_t duration);
int							initialize_simulation(t_diningTable *table);

#endif