/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:44:58 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/10 20:18:54 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	one_coder_case(t_coder *coder);
static int	reserve_dongle(t_coder *coder);
static void	run_loop(t_coder *coder);

void	*coder_loop(void *args)
{
	t_coder	*coder;

	coder = (t_coder *)args;
	while (!is_running(coder->all))
		usleep(100);
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile = get_time(coder->all);
	pthread_mutex_unlock(&coder->mutex);
	if (coder->all->params.nb_coders == 1)
		return (one_coder_case(coder), NULL);
	while (is_running(coder->all))
	{
		if (!reserve_dongle(coder))
			break ;
		run_loop(coder);
		if (coder->all->params.compiles_required > 0
			&& coder->compile_count >= coder->all->params.compiles_required)
		{
			pthread_mutex_lock(&coder->mutex);
			coder->is_finished = true;
			pthread_mutex_unlock(&coder->mutex);
			break ;
		}
	}
	return (NULL);
}

static int	one_coder_case(t_coder *coder)
{
	if (!lock_dongle(coder, coder->l_dongle))
		return (0);
	print_state(coder, take_dongle);
	while (is_running(coder->all))
		usleep(100);
	unlock_dongle(coder->all, coder->l_dongle);
	return (1);
}

static int	reserve_dongle(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		if (!lock_dongle(coder, coder->r_dongle))
			return (0);
		print_state(coder, take_dongle);
		if (!lock_dongle(coder, coder->l_dongle))
		{
			unlock_dongle(coder->all, coder->r_dongle);
			return (0);
		}
		print_state(coder, take_dongle);
	}
	else
	{
		if (!lock_dongle(coder, coder->l_dongle))
			return (0);
		print_state(coder, take_dongle);
		if (!lock_dongle(coder, coder->r_dongle))
		{
			unlock_dongle(coder->all, coder->l_dongle);
			return (0);
		}
		print_state(coder, take_dongle);
	}
	return (1);
}

static void	run_loop(t_coder *coder)
{
	coder_compile(coder);
	unlock_dongle(coder->all, coder->l_dongle);
	unlock_dongle(coder->all, coder->r_dongle);
	coder_debug(coder);
	coder_refactor(coder);
}
