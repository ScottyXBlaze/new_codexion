/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:46:57 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 21:46:57 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	can_take_dongle(t_all *all, t_dongle *dongle)
{
	return (get_time(all) >= dongle->available_at);
}

void	unlock_dongle(t_all *all, t_dongle *dongle)
{
	dongle->available_at = get_time(all) + all->params.dongle_cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

void	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	if (coder->all->params.scheduler == fifo)
		lock_dongle_fifo(coder, dongle);
	else
		lock_dongle_edf(coder, dongle);
}
