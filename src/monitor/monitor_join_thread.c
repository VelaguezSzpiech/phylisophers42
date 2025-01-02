
#include "philo.h"

short	join_thread(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->param->nb_philo)
	{
		pthread_join(env->philo[i]->thread, NULL);
		i++;
	}
	pthread_join(env->monitor_thread, NULL);
	return (0);
}
