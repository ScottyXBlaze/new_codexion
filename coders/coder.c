/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:44:58 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 21:54:33 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static void	coder_compile(t_coder *coder);
static void	coder_debug(t_coder *coder);
static void	coder_refactor(t_coder *coder);
static int	one_coder_case(t_coder *coder);

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
		if (coder->id % 2 == 0)
		{
			if (!lock_dongle(coder, coder->r_dongle))
				break ;
			print_state(coder, take_dongle);
			if (!lock_dongle(coder, coder->l_dongle))
			{
				unlock_dongle(coder->all, coder->r_dongle);
				break ;
			}
			print_state(coder, take_dongle);
		}
		else
		{
			if (!lock_dongle(coder, coder->l_dongle))
				break ;
			print_state(coder, take_dongle);
			if (!lock_dongle(coder, coder->r_dongle))
			{
				unlock_dongle(coder->all, coder->l_dongle);
				break ;
			}
			print_state(coder, take_dongle);
		}
		coder_compile(coder);
		unlock_dongle(coder->all, coder->l_dongle);
		unlock_dongle(coder->all, coder->r_dongle);
		coder_debug(coder);
		coder_refactor(coder);
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

static void	coder_compile(t_coder *coder)
{
	print_state(coder, compile);
	ft_sleep(coder->all->params.compile, coder->all);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	coder->last_compile = get_time(coder->all);
	pthread_mutex_unlock(&coder->mutex);
}

static void	coder_debug(t_coder *coder)
{
	print_state(coder, debug);
	ft_sleep(coder->all->params.debug, coder->all);
}

static void	coder_refactor(t_coder *coder)
{
	print_state(coder, refactor);
	ft_sleep(coder->all->params.refactor, coder->all);
}

void	print_state(t_coder *coder, t_state state)
{
	long int	time;

	pthread_mutex_lock(&coder->all->message_mutex);
	time = get_time(coder->all);
	if (is_running(coder->all) || state == burned_out)
	{
		if (state == take_dongle)
			printf("%ld %d has taken a dongle\n", time, coder->id);
		else if (state == compile)
			printf("%ld %d is compiling\n", time, coder->id);
		else if (state == debug)
			printf("%ld %d is debugging\n", time, coder->id);
		else if (state == refactor)
			printf("%ld %d is refactoring\n", time, coder->id);
		else
			printf("%ld %d burned out\n", time, coder->id);
	}
	pthread_mutex_unlock(&coder->all->message_mutex);
}
