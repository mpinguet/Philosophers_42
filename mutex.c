/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:12:34 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 14:55:44 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_mutex_init(&prog->fork[i], NULL);
		i++;
	}
}

void	destroy_fork(t_prog *prog)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&prog->protect_death);
	while (i < prog->nb_philo)
	{
		pthread_mutex_destroy(&prog->fork[i]);
		pthread_mutex_destroy(&prog->philos[i].meal_mutex);
		i++;
	}
	free(prog->fork);
	free(prog->philos);
	free(prog);
}
