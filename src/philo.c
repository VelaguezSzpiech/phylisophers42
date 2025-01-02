
#include "philo.h"

static short	philo(t_env *env, char **argv)
{
	if (init_param(env, argv))
		return (1);
	if (init_fork(env))
		return (1);
	if (init_philosopher(env))
		return (1);
	if (init_monitor(env))
		return (1);
	join_thread(env);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if ((argc != 5 && argc != 6) || is_int(argc, argv))
	{
		write(2,
			"Usage: ./philo [number_of_philosophers]"
			"[time_to_die] [time_to_eat] [time_to_sleep] "
			"[number_of_times_each_philosopher_must_eat (optional)]\n",
			138);
		return (1);
	}
	env.gc = gc_init();
	if (philo(&env, argv))
	{
		clean(&env);
		write(2, "Error.\n", 8);
		return (1);
	}
	clean(&env);
	return (0);
}
