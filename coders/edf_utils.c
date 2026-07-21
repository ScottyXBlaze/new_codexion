/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:37:43 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/18 15:59:38 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_heap(t_heap *heap, int capacity)
{
	heap->array = malloc(sizeof(t_coder *) * capacity);
	if (!heap->array)
		return (0);
	heap->size = 0;
	heap->capacity = capacity;
	if (pthread_mutex_init(&heap->mutex, NULL))
	{
		free(heap->array);
		return (0);
	}
	return (1);
}

void	destroy_heap(t_heap *heap)
{
	free(heap->array);
	pthread_mutex_destroy(&heap->mutex);
}

int	lock_dongle_edf(t_coder *coder, t_dongle *dongle)
{
	long int	remaining_cooldown;

	heap_push(&dongle->edf, coder);
	while (is_running(coder->all))
	{
		if (heap_peek(&dongle->edf) == coder)
		{
			pthread_mutex_lock(&dongle->mutex);
			if (can_take_dongle(coder->all, dongle))
			{
				heap_pop(&dongle->edf);
				return (1);
			}
			remaining_cooldown = dongle->available_at - get_time(coder->all);
			pthread_mutex_unlock(&dongle->mutex);
			if (remaining_cooldown > 0)
			{
				ft_sleep(remaining_cooldown, coder->all);
				continue ;
			}
		}
		usleep(500);
	}
	return (0);
}

t_coder	*heap_peek(t_heap *heap)
{
	t_coder	*coder;

	pthread_mutex_lock(&heap->mutex);
	coder = NULL;
	if (heap->size > 0)
		coder = heap->array[0];
	pthread_mutex_unlock(&heap->mutex);
	return (coder);
}
