/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:46:18 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/21 13:55:10 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_coders(t_all *all, long int now)
{
	int			i;
	long int	last;
	int		finished;

	i = 0;
	while (i < all->params.nb_coders)
	{
		pthread_mutex_lock(&all->coders[i].mutex);
		last = all->coders[i].last_compile;
		finished = all->coders[i].is_finished;
		pthread_mutex_unlock(&all->coders[i].mutex);
		if (!finished && now - last > all->params.burnout)
		{
			stop_simulation(all);
			print_state(&all->coders[i], burned_out);
			return (1);
		}
		if (!finished)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_loop(void *args)
{
	t_all		*all;
	long int	now;

	all = (t_all *)args;
	while (!is_running(all))
		usleep(500);
	while (is_running(all))
	{
		now = get_time(all);
		if (check_coders(all, now))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
