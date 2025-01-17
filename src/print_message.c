/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:24:04 by vszpiech          #+#    #+#             */
/*   Updated: 2025/01/17 14:18:32 by vszpiech         ###   ########.fr       */
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
	int		is_dead;
	int		is_full;

	current_time = get_time() - philosopher->table->start_time;
	pthread_mutex_lock(&philosopher->table->print_lock);
	is_dead = atomic_load(&philosopher->table->dead);
	is_full = atomic_load(&philosopher->table->is_full);
	if (!is_dead && !is_full)
	{
		printf("%zu %d %s\n", current_time, philosopher->id,
			get_message_text(message));
	}
	else if (message == MESSAGE_DEAD)
	{
		printf("%zu %d %s\n", current_time, philosopher->id,
			get_message_text(message));
	}
	pthread_mutex_unlock(&philosopher->table->print_lock);
}
