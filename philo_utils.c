/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:18:06 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 15:23:59 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	protect_death_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
	{
		philo->prog->death = 1;
		printf("\033[0;31m%ld %d died\n\033[0m", actual_time(philo->prog),
			philo->id);
		pthread_mutex_unlock(&philo->prog->protect_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->protect_death);
	return (0);
}

void	wait_thread(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32 && str[i]))
		i++;
	if (str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	free_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->prog->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->prog->fork[philo->id
			% philo->prog->nb_philo]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->prog->fork[philo->id
			% philo->prog->nb_philo]);
		pthread_mutex_unlock(&philo->prog->fork[philo->id - 1]);
	}
}
