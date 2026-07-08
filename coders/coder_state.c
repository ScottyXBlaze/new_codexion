/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 23:39:22 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 23:59:47 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_compile(t_coder *coder)
{
	print_state(coder, compile);
	ft_sleep(coder->all->params.compile, coder->all);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	coder->last_compile = get_time(coder->all);
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_debug(t_coder *coder)
{
	print_state(coder, debug);
	ft_sleep(coder->all->params.debug, coder->all);
}

void	coder_refactor(t_coder *coder)
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
