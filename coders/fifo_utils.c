/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:35:09 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 17:35:15 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_fifo(t_fifo *fifo, int capacity)
{
	fifo->array = malloc(sizeof(t_coder *) * capacity);
	if (!fifo->array)
		return (0);
	fifo->head = 0;
	fifo->tail = 0;
	fifo->size = 0;
	fifo->capacity = capacity;
	if (pthread_mutex_init(&fifo->mutex, NULL))
	{
		free(fifo->array);
		return (0);
	}
	return (1);
}

void	destroy_fifo(t_fifo *fifo)
{
	free(fifo->array);
	pthread_mutex_destroy(&fifo->mutex);
}
