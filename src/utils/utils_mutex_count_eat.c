
#include "philo.h"

size_t	get_count_eat(t_philosopher *philo)
{
	size_t	count_eat;

	pthread_mutex_lock(&philo->lock_count_meal);
	count_eat = philo->count_to_eat;
	pthread_mutex_unlock(&philo->lock_count_meal);
	return (count_eat);
}

void	increment_count_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->lock_count_meal);
	philo->count_to_eat++;
	pthread_mutex_unlock(&philo->lock_count_meal);
}
