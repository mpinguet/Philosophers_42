/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:17:51 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/27 13:12:19 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_error(int argc, char **argv, t_prog *prog)
{
	prog->nbr_repas = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: invalid number of arguments.\n");
		return (1);
	}
	if (argc == 6)
		prog->nbr_repas = ft_atoi(argv[5]);
	return (0);
}

int	error_management(int argc, char **argv, t_prog *prog)
{
	int	i;
	int	j;

	if (start_error(argc, argv, prog) == 1)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0 && argv[i][j] == '+')
				j++;
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				printf("Error: please enter digits only.\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	prog->start_time = 0;
	return (0);
}
