/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:40:53 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 22:16:44 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	all->running = true;
	return (1);
}
