
#include "philo.h"

void	*routine_handler(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!get_state_end(philo->param))
	{
		if (routine_take_fork(philo))
			break ;
		if (routine_eat(philo))
		{
			routine_free_fork(philo);
			break ;
		}
		if (routine_free_fork(philo))
			break ;
		if (routine_sleep(philo))
			break ;
		if (philo->param->nb_philo % 2 != 0)
			routine_think(philo);
	}
	return (NULL);
}
