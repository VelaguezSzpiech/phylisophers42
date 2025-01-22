
#include "philosopher.h"

static char	*get_message_text(int message)
{
	if (message == MESSAGE_FORK)
		return ("has taken a fork");
	if (message == MESSAGE_EATING)
		return ("is eating");
	if (message == MESSAGE_SLEEPING)
		return ("is sleeping");
	if (message == MESSAGE_THINKING)
		return ("is thinking");
	if (message == MESSAGE_DEAD)
		return ("died");
	return ("Error: not valid message ID");
}

void    print_message(t_philosopher *philosopher, int message)
{
    size_t          current_time;
    t_diningTable   *table;
    int             should_print;

    table = philosopher->table;
    pthread_mutex_lock(&table->check_lock);
    should_print = (!table->dead && !table->is_full) || (message == MESSAGE_DEAD);
    if (!should_print)
    {
        pthread_mutex_unlock(&table->check_lock);
        return;
    }
    current_time = get_time() - table->start_time;
    if (message == MESSAGE_DEAD)
        table->dead = 1;
    pthread_mutex_unlock(&table->check_lock);

    pthread_mutex_lock(&table->print_lock);
    printf("%zu %d %s\n", current_time, philosopher->id, 
           get_message_text(message));
    pthread_mutex_unlock(&table->print_lock);
}
