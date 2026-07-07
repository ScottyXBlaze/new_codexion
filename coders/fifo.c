/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:47:31 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 21:55:33 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	fifo_push(t_fifo *fifo, t_coder *coder)
{
	pthread_mutex_lock(&fifo->mutex);
	if (fifo->size < fifo->capacity)
	{
		fifo->array[fifo->tail] = coder;
		fifo->tail = (fifo->tail + 1) % fifo->capacity;
		fifo->size++;
	}
	pthread_mutex_unlock(&fifo->mutex);
}

t_coder	*fifo_front(t_fifo *fifo)
{
	t_coder	*coder;

	pthread_mutex_lock(&fifo->mutex);
	coder = NULL;
	if (fifo->size > 0)
		coder = fifo->array[fifo->head];
	pthread_mutex_unlock(&fifo->mutex);
	return (coder);
}

void	fifo_pop(t_fifo *fifo)
{
	pthread_mutex_lock(&fifo->mutex);
	if (fifo->size > 0)
	{
		fifo->head = (fifo->head + 1) % fifo->capacity;
		fifo->size--;
	}
	pthread_mutex_unlock(&fifo->mutex);
}

int	lock_dongle_fifo(t_coder *coder, t_dongle *dongle)
{
	long int	remaining_cooldown;

	fifo_push(&dongle->fifo, coder);
	while (is_running(coder->all))
	{
		if (fifo_front(&dongle->fifo) == coder)
		{
			pthread_mutex_lock(&dongle->mutex);
			if (can_take_dongle(coder->all, dongle))
			{
				fifo_pop(&dongle->fifo);
				return (1);
			}
			remaining_cooldown = dongle->available_at - get_time(coder->all);
			pthread_mutex_unlock(&dongle->mutex);
			if (remaining_cooldown > 0)
			{
				if (remaining_cooldown > 1)
					usleep(1000);
				else
					usleep(remaining_cooldown * 1000);
				continue ;
			}
		}
		usleep(100);
	}
	return (0);
}
