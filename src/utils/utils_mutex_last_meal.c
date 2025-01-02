
#include "philo.h"

size_t	get_last_meal(t_philosopher *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->lock_last_meal);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->lock_last_meal);
	return (last_meal);
}

void	update_last_meal(t_philosopher *philo, size_t new_value)
{
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->time_last_meal = new_value;
	pthread_mutex_unlock(&philo->lock_last_meal);
}
