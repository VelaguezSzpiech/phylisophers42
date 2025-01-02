
#include "philo.h"

static void	*routine_monitor_handler(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		if (get_state_end(env->param))
			break ;
		if (check_time_eat(env))
			break ;
		if (check_nb_eat(env))
			break ;
		usleep(50);
	}
	return (NULL);
}

short	init_monitor(t_env *env)
{
	pthread_create(&env->monitor_thread, NULL, routine_monitor_handler, env);
	return (0);
}
