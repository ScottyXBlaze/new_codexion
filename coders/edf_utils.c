/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:37:43 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 17:37:46 by nyramana         ###   ########.fr       */
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
