/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyramana <nyramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 16:50:20 by nyramana          #+#    #+#             */
/*   Updated: 2026/07/10 22:58:38 by nyramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static int			validate_args(int argc, char **argv);
static t_scheduler	scheduler(char *str);
static void print_help(void);

int	parsers(int argc, char **argv, t_all *all)
{
	if (validate_args(argc, argv) == 0)
		return (0);
	all->params.nb_coders = atoi(argv[1]);
	all->params.burnout = atoi(argv[2]);
	all->params.compile = atoi(argv[3]);
	all->params.debug = atoi(argv[4]);
	all->params.refactor = atoi(argv[5]);
	all->params.compiles_required = atoi(argv[6]);
	all->params.dongle_cooldown = atoi(argv[7]);
	all->params.scheduler = scheduler(argv[8]);
	if (all->params.nb_coders < 1)
	{
		printf("[ERROR] Not enough coder\n");
		return (print_help(), 0);
	}
	return (1);
}

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 9)
	{
		printf("[ERROR] Invalid number of argument %d\n", argc - 1);
		printf("Should be 8\n");
		return (print_help(), 0);
	}
	i = 1;
	while (i < 8)
	{
		if (!validate_int(argv[i]))
		{
			printf("Check parameter nb %d\n", i - 1);
			return (print_help(), 0);
		}
		i++;
	}
	if (!validate_scheduler(argv[i]))
	{
		printf("Check last parameter\n");
		return (print_help(), 0);
	}
	return (1);
}

static t_scheduler	scheduler(char *str)
{
	if (strcmp(str, "fifo") == 0)
		return (fifo);
	return (edf);
}

static void print_help(void)
{
	printf("[USAGE] ./codexion number_of_coders time_to_burnout time_to_compile ");
	printf("time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler\n");
}
