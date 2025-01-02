
#include "philo.h"

void	clean(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->param->nb_philo)
	{
		pthread_mutex_destroy(&env->param->forks[i]);
		pthread_mutex_destroy(&env->philo[i]->lock_last_meal);
		pthread_mutex_destroy(&env->philo[i]->lock_count_meal);
		i++;
	}
	pthread_mutex_destroy(&env->param->lock_printf);
	pthread_mutex_destroy(&env->param->lock_state_end);
	gc_clean(env->gc);
}
