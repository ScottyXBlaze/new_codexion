/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:40:53 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/11 13:16:08 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <unistd.h>

static void	join_coders(t_coder *coders);

int	init_all(t_all *all)
{
	if (pthread_mutex_init(&all->message_mutex, NULL))
	{
		destroy_all(all);
		return (0);
	}
	if (pthread_mutex_init(&all->running_mutex, NULL))
	{
		destroy_all(all);
		return (0);
	}
	all->start_time = get_time(all);
	ft_sleep(100000, all);
	pthread_mutex_lock(&all->running_mutex);
	all->running = true;
	pthread_mutex_unlock(&all->running_mutex);
	join_coders(all->coders);
	return (1);
}

static void	join_coders(t_coder *coders)
{
	int	i;
	int	nb_coders;

	i = 0;
	nb_coders = coders->all->params.nb_coders;
	while (i < nb_coders)
	{
		if (pthread_join(coders[i].thread, NULL))
			return ;
		i++;
	}
}
