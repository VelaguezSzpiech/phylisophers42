
#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_gc
{
	t_list			*head;
}					t_gc;

typedef struct s_param
{
	size_t			nb_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			nb_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_forks;
	size_t			start_time;
	volatile int	state_end;
	pthread_mutex_t	lock_state_end;
	pthread_mutex_t	lock_printf;
}					t_param;

typedef struct s_philosopher
{
	size_t			id;
	pthread_t		thread;
	size_t			time_last_meal;
	pthread_mutex_t	lock_last_meal;
	size_t			count_to_eat;
	pthread_mutex_t	lock_count_meal;
	struct s_param	*param;
}					t_philosopher;

typedef struct s_env
{
	t_param			*param;
	t_gc			*gc;
	t_philosopher	**philo;
	pthread_t		monitor_thread;
}					t_env;

#endif