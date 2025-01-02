
#include "philo.h"

void	debug_print_param(t_env *env)
{
	printf("List Param:\n");
	printf(" nb_philo: %ld\n", env->param->nb_philo);
	printf(" time_die: %ld\n", env->param->time_die);
	printf(" time_eat: %ld\n", env->param->time_eat);
	printf(" time_sleep: %ld\n", env->param->time_sleep);
	printf(" nb_to_eat: %ld\n", env->param->nb_to_eat);
	printf(" state_end: %d\n", env->param->state_end);
}
