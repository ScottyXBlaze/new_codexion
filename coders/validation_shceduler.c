/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_shceduler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 16:54:41 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/07 17:13:11 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	validate_scheduler(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (strcmp(str, "fifo") == 0 || strcmp(str, "edf") == 0)
		return (1);
	printf("[ERROR] Invalid scheduler parameter %s\n", str);
	printf("Should be 'fifo' of 'edf'\n");
	return (0);
}
