/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:55:58 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/18 16:00:42 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_higher_priority(t_coder *a, t_coder *b)
{
	long int	a_deadline;
	long int	b_deadline;
	long int	last;

	pthread_mutex_lock(&a->mutex);
	last = a->last_compile;
	pthread_mutex_unlock(&a->mutex);
	a_deadline = last + a->all->params.burnout;
	pthread_mutex_lock(&b->mutex);
	last = b->last_compile;
	pthread_mutex_unlock(&b->mutex);
	b_deadline = last + b->all->params.burnout;
	if (a_deadline != b_deadline)
		return (a_deadline < b_deadline);
	return (a->id < b->id);
}

static int	get_smallest_child(t_heap *heap, int index)
{
	int	left;
	int	right;
	int	smallest;

	left = (index * 2) + 1;
	right = (index * 2) + 2;
	smallest = index;
	if (left < heap->size && is_higher_priority(heap->array[left],
			heap->array[smallest]))
		smallest = left;
	if (right < heap->size && is_higher_priority(heap->array[right],
			heap->array[smallest]))
		smallest = right;
	return (smallest);
}

void	heap_push(t_heap *heap, t_coder *coder)
{
	int	index;
	int	parent;

	pthread_mutex_lock(&heap->mutex);
	if (heap->size >= heap->capacity)
	{
		pthread_mutex_unlock(&heap->mutex);
		return ;
	}
	index = heap->size;
	heap->array[index] = coder;
	heap->size++;
	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!is_higher_priority(heap->array[index], heap->array[parent]))
			break ;
		coder = heap->array[index];
		heap->array[index] = heap->array[parent];
		heap->array[parent] = coder;
		index = parent;
	}
	pthread_mutex_unlock(&heap->mutex);
}

static void	sift_down(t_heap *heap)
{
	int		index;
	int		smallest;
	t_coder	*tmp;

	index = 0;
	while (1)
	{
		smallest = get_smallest_child(heap, index);
		if (smallest == index)
			break ;
		tmp = heap->array[index];
		heap->array[index] = heap->array[smallest];
		heap->array[smallest] = tmp;
		index = smallest;
	}
}

void	heap_pop(t_heap *heap)
{
	pthread_mutex_lock(&heap->mutex);
	if (heap->size <= 0)
	{
		pthread_mutex_unlock(&heap->mutex);
		return ;
	}
	heap->size--;
	if (heap->size == 0)
	{
		pthread_mutex_unlock(&heap->mutex);
		return ;
	}
	heap->array[0] = heap->array[heap->size];
	sift_down(heap);
	pthread_mutex_unlock(&heap->mutex);
}
