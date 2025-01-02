
#include "philo.h"

short	routine_take_fork(t_philosopher *philo)
{
	if (philo->param->nb_philo == 1)
	{
		print_state_philo(philo, LOG_TAKE_FORK, get_time_simulation(philo));
		ft_sleep(philo->param->time_die);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->param->forks[philo->id]);
		pthread_mutex_lock(&philo->param->forks[(philo->id + 1)
			% philo->param->nb_philo]);
	}
	else
	{
		pthread_mutex_lock(&philo->param->forks[(philo->id + 1)
			% philo->param->nb_philo]);
		pthread_mutex_lock(&philo->param->forks[philo->id]);
	}
	print_state_philo(philo, LOG_TAKE_FORK, get_time_simulation(philo));
	print_state_philo(philo, LOG_TAKE_FORK, get_time_simulation(philo));
	return (0);
}

short	routine_free_fork(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->param->forks[philo->id]);
		pthread_mutex_unlock(&philo->param->forks[(philo->id + 1)
			% philo->param->nb_philo]);
	}
	else
	{
		pthread_mutex_unlock(&philo->param->forks[(philo->id + 1)
			% philo->param->nb_philo]);
		pthread_mutex_unlock(&philo->param->forks[philo->id]);
	}
	return (0);
}
