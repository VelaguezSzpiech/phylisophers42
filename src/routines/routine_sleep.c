
#include "philo.h"

short	routine_sleep(t_philosopher *philo)
{
	if (get_state_end(philo->param))
		return (1);
	print_state_philo(philo, LOG_SLEEP, get_time_simulation(philo));
	ft_sleep(philo->param->time_sleep);
	return (0);
}
