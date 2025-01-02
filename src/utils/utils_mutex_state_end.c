
#include "philo.h"

short	get_state_end(t_param *param)
{
	short	state;

	pthread_mutex_lock(&param->lock_state_end);
	state = param->state_end;
	pthread_mutex_unlock(&param->lock_state_end);
	return (state);
}

void	update_state_end(t_param *param, int new_value)
{
	pthread_mutex_lock(&param->lock_state_end);
	param->state_end = new_value;
	pthread_mutex_unlock(&param->lock_state_end);
}
