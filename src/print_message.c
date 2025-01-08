/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:51 by vela              #+#    #+#             */
/*   Updated: 2025/01/08 19:47:31 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_message(t_philosopher *philosopher, int message)
{
	size_t	current_time;

	current_time = get_time() - philosopher->table->start_time;
	pthread_mutex_lock(&philosopher->table->print_lock);
	if (!philosopher->table->dead && !philosopher->table->is_full)
	{
		printf("%ld ", current_time);
		printf("%d ", philosopher->id);
		printf("%s\n", get_message_text(message));
	}
	pthread_mutex_unlock(&philosopher->table->print_lock);
}
