/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:46:18 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 22:07:16 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitor_loop(void *args)
{
	t_all		*all;
	long int	last;
	bool		finished;
	bool		end_simulation;
	int			i;
	long int	now;

	all = (t_all *)args;
	while (is_running(all) && all->coders == NULL)
		usleep(100);
	while (is_running(all))
	{
		now = get_time(all);
		i = 0;
		finished = true;
		end_simulation = true;
		while (i < all->params.nb_coders)
		{
			pthread_mutex_lock(&all->coders[i].mutex);
			last = all->coders[i].last_compile;
			finished = all->coders[i].is_finished;
			if (!finished)
				end_simulation = false;
			pthread_mutex_unlock(&all->coders[i].mutex);
			if (now - last > all->params.burnout && !finished)
			{
				stop_simulation(all);
				print_state(&all->coders[i], burned_out);
				return (NULL);
			}
			i++;
		}
		if (end_simulation)
		{
			stop_simulation(all);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
