/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:49:13 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 17:55:18 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_thread_coders(t_coder *coders);
static int	set_memory(t_all *all);

int	init_coders(t_all *all)
{
	int	i;

	i = 0;
	set_memory(all);
	while (i < all->params.nb_coders)
	{
		all->coders[i].id = i + 1;
		all->coders[i].all = all;
		all->coders[i].l_dongle = &all->dongles[i];
		all->coders[i].r_dongle = &all->dongles[(i + 1)
			% all->params.nb_coders];
		all->coders[i].compile_count = 0;
		all->coders[i].last_compile = get_time(all);
		all->coders[i].is_finished = false;
		all->coders[i].deadline = 0;
		if (pthread_mutex_init(&all->coders[i].mutex, NULL))
		{
			destroy_dongles(all);
			return (0);
		}
		i++;
	}
	if (pthread_create(&all->monitor, NULL, monitor_loop, all))
	{
		destroy_all(all);
		return (0);
	}
	init_thread_coders(all->coders);
	return (1);
}

static int	set_memory(t_all *all)
{
	all->coders = malloc(sizeof(t_coder) * all->params.nb_coders);
	if (all->coders == NULL)
	{
		destroy_all(all);
		return (0);
	}
	all->coders = memset(all->coders, 0, sizeof(t_coder)
			* all->params.nb_coders);
	return (1);
}

static void	init_thread_coders(t_coder *coders)
{
	int	i;
	int	nb_coders;

	i = 0;
	nb_coders = coders[0].all->params.nb_coders;
	while (i < nb_coders)
	{
		if (pthread_create(&coders[i].thread, NULL, coder_loop, &coders[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < nb_coders)
	{
		if (pthread_join(coders[i].thread, NULL))
			return ;
		i++;
	}
	if (pthread_join(coders->all->monitor, NULL))
		return ;
}
