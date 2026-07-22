/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:30:13 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/22 14:48:29 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	destroy_coders(t_coder *coders);

void	destroy_all(t_all *all)
{
	pthread_mutex_destroy(&all->running_mutex);
	pthread_mutex_destroy(&all->message_mutex);
	destroy_dongles(all);
	destroy_coders(all->coders);
}


static int	destroy_coders(t_coder *coders)
{
	free(coders);
	coders = NULL;
	return (1);
}
