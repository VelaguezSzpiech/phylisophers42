
#include "philo.h"

short	routine_eat(t_philosopher *philo)
{
	if (get_state_end(philo->param))
		return (1);
	update_last_meal(philo, get_time_simulation(philo));
	increment_count_eat(philo);
	print_state_philo(philo, LOG_EATING, get_time_simulation(philo));
	ft_sleep(philo->param->time_eat);
	return (0);
}
