
#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>


# define LOG_TAKE_FORK "has taken a fork"
# define LOG_EATING "is eating"
# define LOG_SLEEP "is sleeping"
# define LOG_THINKING "is thinking"
# define LOG_DIED "died"

# define PARSING_MIN 1

# define INT_MIN -2147483648
# define INT_MAX 2147483647


short		init_fork(t_env *env);
short		init_param(t_env *env, char **argv);
short		init_philosopher(t_env *env);


short		init_monitor(t_env *env);
short		join_thread(t_env *env);
short		check_time_eat(t_env *env);
short		check_nb_eat(t_env *env);


void		*routine_handler(void *arg);
short		routine_take_fork(t_philosopher *philo);
short		routine_eat(t_philosopher *philo);
short		routine_free_fork(t_philosopher *philo);
short		routine_sleep(t_philosopher *philo);
short		routine_think(t_philosopher *philo);


size_t		get_last_meal(t_philosopher *philo);
void		update_last_meal(t_philosopher *philo, size_t new_value);
short		get_state_end(t_param *param);
void		update_state_end(t_param *param, int new_value);
void		increment_count_eat(t_philosopher *philo);
size_t		get_count_eat(t_philosopher *philo);
void		clean(t_env *env);
void		ft_sleep(size_t time);
size_t		get_time(void);
size_t		get_delay_last_meal(t_philosopher *philo);
size_t		get_time_simulation(t_philosopher *philo);
void		print_state_philo(t_philosopher *philo, char *log,
				size_t timestamp);


void		debug_print_param(t_env *env);


long long	ft_atoll(const char *str);
short		is_int(size_t size, char **arg);
size_t		ft_strlen(char *s);
void		clean(t_env *env);

t_gc		*gc_init(void);
short		gc_add(t_gc *gc, void *ptr);
short		gc_remove_one(t_gc *gc, void *ptr);
void		gc_clean(t_gc *gc);
void		gc_print_debug(t_gc *gc);

#endif