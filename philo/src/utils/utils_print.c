
#include "philo.h"

void	print_state_philo(t_philosopher *philo, char *log, size_t timestamp)
{
	if (get_state_end(philo->param) && log[0] != 'd')
		return ;
	pthread_mutex_lock(&philo->param->lock_printf);
	printf("%zu %zu %s\n", timestamp, philo->id + 1, log);
	pthread_mutex_unlock(&philo->param->lock_printf);
}
