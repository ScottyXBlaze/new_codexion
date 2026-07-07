/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 11:48:24 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 17:42:26 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_all	all;

	memset(&all, 0, sizeof(all));
	if (!parsers(argc, argv, &all))
		return (1);
	if (!init_dongles(&all) || !init_all(&all))
		return (1);
	return (0);
}
