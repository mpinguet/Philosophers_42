/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:17:42 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 15:26:38 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_start_prog(t_prog *prog)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	prog->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long	actual_time_2(void)
{
	long			i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (i);
}

long	actual_time(t_prog *prog)
{
	long			i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	i -= prog->start_time;
	return (i);
}

int	error_eat(t_philo *philo)
{
	if (check_time_eat(philo) == 1)
	{
		free_fork(philo);
		return (1);
	}
	return (0);
}
